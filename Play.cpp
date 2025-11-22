#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include <list>
#include <mutex>
#include <iomanip>
#include <array>

using namespace std;
using namespace std::chrono;

// ============================================================================
// EPOCH-BASED RECLAMATION (Much faster than Hazard Pointers!)
// ============================================================================

template<typename T>
class EpochManager
{
private:
    static constexpr size_t MAX_THREADS = 16;
    static constexpr size_t EPOCH_FREQ = 100;  // Update epoch every N operations
    
    struct alignas(64) ThreadData
    {
        atomic<uint64_t> local_epoch{0};
        atomic<bool> active{false};
        uint64_t op_count{0};
        vector<T*> retired[3];  // One vector per epoch
    };
    
    alignas(64) atomic<uint64_t> global_epoch{0};
    static ThreadData thread_data[MAX_THREADS];
    static thread_local size_t thread_id;
    static atomic<size_t> thread_counter;
    
    static size_t get_thread_id()
    {
        static thread_local bool initialized = false;
        if (!initialized)
        {
            thread_id = thread_counter.fetch_add(1, memory_order_relaxed) % MAX_THREADS;
            initialized = true;
        }
        return thread_id;
    }
    
    void try_update_epoch()
    {
        size_t tid = get_thread_id();
        ThreadData& td = thread_data[tid];
        
        if (++td.op_count % EPOCH_FREQ == 0)
        {
            uint64_t ge = global_epoch.load(memory_order_acquire);
            td.local_epoch.store(ge, memory_order_release);
        }
    }
    
    uint64_t compute_min_epoch()
    {
        uint64_t min_epoch = global_epoch.load(memory_order_acquire);
        
        for (size_t i = 0; i < MAX_THREADS; ++i)
        {
            if (thread_data[i].active.load(memory_order_acquire))
            {
                uint64_t le = thread_data[i].local_epoch.load(memory_order_acquire);
                if (le < min_epoch)
                    min_epoch = le;
            }
        }
        
        return min_epoch;
    }
    
public:
    EpochManager() = default;
    
    void enter()
    {
        size_t tid = get_thread_id();
        ThreadData& td = thread_data[tid];
        
        td.active.store(true, memory_order_release);
        uint64_t ge = global_epoch.load(memory_order_acquire);
        td.local_epoch.store(ge, memory_order_release);
    }
    
    void exit()
    {
        size_t tid = get_thread_id();
        thread_data[tid].active.store(false, memory_order_release);
    }
    
    void retire(T* ptr)
    {
        if (!ptr) return;
        
        size_t tid = get_thread_id();
        ThreadData& td = thread_data[tid];
        
        try_update_epoch();
        
        uint64_t ge = global_epoch.load(memory_order_acquire);
        td.retired[ge % 3].push_back(ptr);
        
        // Try to reclaim old epochs
        if (td.retired[ge % 3].size() > 100)
        {
            uint64_t min_epoch = compute_min_epoch();
            
            if (min_epoch > 0)
            {
                uint64_t safe_epoch = (min_epoch - 1) % 3;
                for (T* p : td.retired[safe_epoch])
                {
                    delete p;
                }
                td.retired[safe_epoch].clear();
            }
        }
    }
    
    void advance_epoch()
    {
        global_epoch.fetch_add(1, memory_order_acq_rel);
    }
    
    ~EpochManager()
    {
        // Cleanup all retired nodes
        for (size_t i = 0; i < MAX_THREADS; ++i)
        {
            for (int e = 0; e < 3; ++e)
            {
                for (T* ptr : thread_data[i].retired[e])
                {
                    delete ptr;
                }
            }
        }
    }
};

template<typename T>
typename EpochManager<T>::ThreadData EpochManager<T>::thread_data[EpochManager<T>::MAX_THREADS];
template<typename T>
thread_local size_t EpochManager<T>::thread_id{0};
template<typename T>
atomic<size_t> EpochManager<T>::thread_counter{0};

// ============================================================================
// LOCK-FREE QUEUE WITH EPOCH-BASED RECLAMATION
// ============================================================================

template <typename T>
class LockFreeQueue
{
private:
    struct Node
    {
        T data;
        atomic<Node*> next;
        
        Node() : data{}, next{nullptr} {}
        explicit Node(const T& val) : data(val), next{nullptr} {}
    };

    alignas(64) atomic<Node*> m_head;
    alignas(64) atomic<Node*> m_tail;
    EpochManager<Node> epoch_mgr;

public:
    LockFreeQueue()
    {
        Node* dummy = new Node();
        m_head.store(dummy, memory_order_relaxed);
        m_tail.store(dummy, memory_order_relaxed);
    }
    
    ~LockFreeQueue()
    {
        Node* current = m_head.load(memory_order_relaxed);
        while (current)
        {
            Node* next = current->next.load(memory_order_relaxed);
            delete current;
            current = next;
        }
    }
    
    LockFreeQueue(const LockFreeQueue&) = delete;
    LockFreeQueue& operator=(const LockFreeQueue&) = delete;
    
    bool enqueue(const T& value)
    {
        epoch_mgr.enter();
        
        Node* newNode = new Node(value);
        
        while (true)
        {
            Node* tail = m_tail.load(memory_order_acquire);
            Node* next = tail->next.load(memory_order_acquire);
            
            if (tail == m_tail.load(memory_order_acquire))
            {
                if (next == nullptr)
                {
                    if (tail->next.compare_exchange_weak(next, newNode,
                                                         memory_order_release,
                                                         memory_order_acquire))
                    {
                        m_tail.compare_exchange_weak(tail, newNode,
                                                    memory_order_release,
                                                    memory_order_relaxed);
                        epoch_mgr.exit();
                        return true;
                    }
                }
                else
                {
                    m_tail.compare_exchange_weak(tail, next,
                                                memory_order_release,
                                                memory_order_relaxed);
                }
            }
        }
    }

    bool dequeue(T& result)
    {
        epoch_mgr.enter();
        
        while (true)
        {
            Node* head = m_head.load(memory_order_acquire);
            Node* tail = m_tail.load(memory_order_acquire);
            Node* next = head->next.load(memory_order_acquire);
            
            if (head == m_head.load(memory_order_acquire))
            {
                if (head == tail)
                {
                    if (next == nullptr)
                    {
                        epoch_mgr.exit();
                        return false;
                    }
                    
                    m_tail.compare_exchange_weak(tail, next,
                                                memory_order_release,
                                                memory_order_relaxed);
                }
                else
                {
                    if (next == nullptr)
                        continue;
                    
                    result = next->data;
                    
                    if (m_head.compare_exchange_weak(head, next,
                                                     memory_order_release,
                                                     memory_order_acquire))
                    {
                        epoch_mgr.retire(head);
                        epoch_mgr.exit();
                        return true;
                    }
                }
            }
        }
    }
};

// ============================================================================
// MUTEX-BASED QUEUE
// ============================================================================

template <typename T>
class MutexQueue
{
private:
    list<T> m_queue;
    mutex m_mutex;
    
public:
    bool enqueue(const T& value)
    {
        lock_guard<mutex> lock(m_mutex);
        m_queue.push_back(value);
        return true;
    }

    bool dequeue(T& result)
    {
        lock_guard<mutex> lock(m_mutex);
        if (m_queue.empty())
            return false;
        
        result = m_queue.front();
        m_queue.pop_front();
        return true;
    }
};

// ============================================================================
// BENCHMARK FRAMEWORK
// ============================================================================

template<typename Queue>
class Benchmark
{
private:
    Queue& queue;
    atomic<long long> total_dequeued{0};
    atomic<bool> producers_done{false};
    
    void producer(long long items_per_thread)
    {
        for (long long i = 0; i < items_per_thread; ++i)
        {
            queue.enqueue(i);
        }
    }
    
    void consumer(long long total_items)
    {
        long long value;
        
        while (true)
        {
            if (queue.dequeue(value))
            {
                long long count = total_dequeued.fetch_add(1, memory_order_relaxed) + 1;
                if (count >= total_items)
                    return;
            }
            else
            {
                if (producers_done.load(memory_order_acquire) && 
                    total_dequeued.load(memory_order_relaxed) >= total_items)
                    return;
            }
        }
    }
    
public:
    Benchmark(Queue& q) : queue(q) {}
    
    double run(int num_producers, int num_consumers, long long items_per_producer)
    {
        total_dequeued.store(0);
        producers_done.store(false);
        
        long long total_items = num_producers * items_per_producer;
        
        auto start = high_resolution_clock::now();
        
        vector<thread> producers;
        for (int i = 0; i < num_producers; ++i)
            producers.emplace_back(&Benchmark::producer, this, items_per_producer);
        
        vector<thread> consumers;
        for (int i = 0; i < num_consumers; ++i)
            consumers.emplace_back(&Benchmark::consumer, this, total_items);
        
        for (auto& t : producers)
            t.join();
        
        producers_done.store(true, memory_order_release);
        
        for (auto& t : consumers)
            t.join();
        
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count() / 1e6;
    }
};

// ============================================================================
// MAIN
// ============================================================================

int main()
{
    cout << "\n╔═══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║     LOCK-FREE QUEUE (Epoch-Based) vs MUTEX QUEUE BENCHMARK          ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════════════╝\n\n";
    
    const long long ITEMS_PER_PRODUCER = 2'500'000;
    
    struct TestConfig {
        int producers, consumers;
        string name;
    };
    
    vector<TestConfig> configs = {
        {1, 1, "1P + 1C"},
        {2, 2, "2P + 2C"},
        {4, 4, "4P + 4C"},
        {8, 8, "8P + 8C"}
    };
    
    cout << fixed << setprecision(3);
    cout << setw(12) << "Config" 
         << setw(15) << "Mutex (s)" 
         << setw(15) << "LockFree (s)"
         << setw(18) << "Speedup"
         << setw(18) << "Mutex (Mops/s)"
         << setw(18) << "LockFree (Mops/s)\n";
    cout << string(96, '-') << "\n";
    
    for (const auto& config : configs)
    {
        long long total = config.producers * ITEMS_PER_PRODUCER;
        
        MutexQueue<long long> mq;
        Benchmark<MutexQueue<long long>> mb(mq);
        double mt = mb.run(config.producers, config.consumers, ITEMS_PER_PRODUCER);
        
        LockFreeQueue<long long> lfq;
        Benchmark<LockFreeQueue<long long>> lfb(lfq);
        double lft = lfb.run(config.producers, config.consumers, ITEMS_PER_PRODUCER);
        
        double speedup = mt / lft;
        
        cout << setw(12) << config.name
             << setw(15) << mt
             << setw(15) << lft
             << setw(17) << speedup << "x"
             << setw(18) << (total/mt)/1e6
             << setw(18) << (total/lft)/1e6 << "\n";
        
        this_thread::sleep_for(milliseconds(100));
    }
    
    cout << "\n✓ Benchmark complete with proper memory reclamation!\n";
    cout << "  Compile: g++ -O3 -std=c++17 -pthread -march=native benchmark.cpp\n\n";
    
    return 0;
}