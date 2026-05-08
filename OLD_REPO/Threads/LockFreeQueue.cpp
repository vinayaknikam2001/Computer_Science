#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;
using namespace std::chrono;

#define MAX_TESTS 10000000
#define MAX_T_CNT 4

// ============================================================================
// LOCK-FREE QUEUE WITHOUT HAZARD POINTERS (Default Memory Order - Simplest)
// ============================================================================

template <typename T>
class LockFreeQ
{
public: // <-- make Node public so it can be used in main
    struct Node
    {
        T data;
        std::atomic<Node*> next;
        
        Node() : data{}, next{nullptr} {}
        explicit Node(const T& val) : data(val), next{nullptr} {}
    };

private: // <-- keep the internals private
    alignas(64) std::atomic<Node*> m_head;
    alignas(64) std::atomic<Node*> m_tail;

public:
    LockFreeQ()
    {
        Node* dummy = new Node();
        m_head.store(dummy);
        m_tail.store(dummy);
    }
    
    ~LockFreeQ()
    {
        Node* current = m_head.load();
        while (current)
        {
            Node* next = current->next.load();
            delete current;
            current = next;
        }
    }
    
    LockFreeQ(const LockFreeQ&) = delete;
    LockFreeQ& operator=(const LockFreeQ&) = delete;
    
    bool enqueue(const T& data)
    {
        Node* newNode = new Node(data);
        
        while (true)
        {
            Node* tail = m_tail.load();
            Node* next = tail->next.load();
            
            if (tail == m_tail.load())
            {
                if (next == nullptr)
                {
                    if (tail->next.compare_exchange_weak(next, newNode))
                    {
                        m_tail.compare_exchange_weak(tail, newNode);
                        return true;
                    }
                }
                else
                {
                    m_tail.compare_exchange_weak(tail, next);
                }
            }
        }
    }

    bool dequeue(T& returnValue)
    {
        while (true)
        {
            Node* head = m_head.load();
            Node* tail = m_tail.load();
            Node* next = head->next.load();
            
            if (head == m_head.load())
            {
                if (head == tail)
                {
                    if (next == nullptr)
                    {
                        return false;
                    }
                    m_tail.compare_exchange_weak(tail, next);
                }
                else
                {
                    if (next == nullptr)
                        continue;
                    
                    returnValue = next->data;
                    
                    if (m_head.compare_exchange_weak(head, next))
                    {
                        // Intentionally NOT deleting 'head' - memory leak for speed
                        return true;
                    }
                }
            }
        }
    }
};

// ============================================================================
// MUTEX-BASED QUEUE (For Comparison)
// ============================================================================

template <typename T>
class MutexQueue
{
private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    
public:
    MutexQueue() = default;
    
    bool enqueue(const T& value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push_back(value);
        return true;
    }

    bool dequeue(T& result)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queue.empty())
            return false;
        
        result = m_queue.front();
        m_queue.pop_front();
        return true;
    }
};

// ============================================================================
// BENCHMARK
// ============================================================================

template<typename Queue>
double benchmark_queue(Queue& q, int producers, int consumers, lli items_per_producer)
{
    atomic<lli> total_dequeued{0};
    atomic<bool> producers_done{false};
    lli total_items = producers * items_per_producer;
    
    auto producer_fn = [&](lli items) {
        for (lli i = 0; i < items; ++i)
        {
            q.enqueue(i);
        }
    };
    
    auto consumer_fn = [&]() {
        lli val;
        while (true)
        {
            if (q.dequeue(val))
            {
                lli count = total_dequeued.fetch_add(1) + 1;
                if (count >= total_items)
                    return;
            }
            else
            {
                if (producers_done.load() && total_dequeued.load() >= total_items)
                    return;
            }
        }
    };
    
    auto start = high_resolution_clock::now();
    
    vector<thread> threads;
    for (int i = 0; i < producers; ++i)
        threads.emplace_back(producer_fn, items_per_producer);
    for (int i = 0; i < consumers; ++i)
        threads.emplace_back(consumer_fn);
    
    for (int i = 0; i < producers; ++i)
        threads[i].join();
    producers_done.store(true);
    
    for (size_t i = producers; i < threads.size(); ++i)
        threads[i].join();
    
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count() / 1e6;
}

// ============================================================================
// MAIN
// ============================================================================

int main()
{
    struct Config {
        int producers;
        int consumers;
        string name;
    };
    
    vector<Config> configs = {
        {1, 1, "1 Producer + 1 Consumer"},
        {2, 2, "2 Producers + 2 Consumers"},
        {4, 4, "4 Producers + 4 Consumers"},
        {8, 8, "8 Producers + 8 Consumers"}
    };
    
    const lli ITEMS_PER_PRODUCER = 2'500'000;

    cout << "Benchmark: Mutex Queue vs Lock-Free Queue\n";
    cout << "Items per producer: " << ITEMS_PER_PRODUCER << "\n\n";

    cout << left << setw(25) << "Configuration"
         << setw(15) << "Mutex(s)"
         << setw(15) << "LockFree(s)"
         << setw(12) << "Speedup"
         << setw(15) << "LF Mops/s"
         << "\n";

    cout << string(80, '-') << "\n";

    for (const auto& cfg : configs)
    {
        lli total_items = cfg.producers * ITEMS_PER_PRODUCER;

        // Run Mutex queue
        MutexQueue<lli> mq;
        double t_mutex = benchmark_queue(
            mq, cfg.producers, cfg.consumers, ITEMS_PER_PRODUCER
        );

        // Run Lock-free queue
        LockFreeQ<lli> lfq;
        double t_lockfree = benchmark_queue(
            lfq, cfg.producers, cfg.consumers, ITEMS_PER_PRODUCER
        );

        double speedup = t_mutex / t_lockfree;
        double mops = (total_items / t_lockfree) / 1e6;

        cout << left << setw(25) << cfg.name
             << setw(15) << fixed << setprecision(4) << t_mutex
             << setw(15) << fixed << setprecision(4) << t_lockfree
             << setw(12) << fixed << setprecision(2) << speedup
             << setw(15) << fixed << setprecision(2) << mops
             << "\n";
    }

    return 0;
}
