#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <array>

// Simple Hazard Pointer Manager
template<typename T>
class SimpleHazardPointers {
private:
    static constexpr size_t MAX_THREADS = 16;
    static constexpr size_t HAZARDS_PER_THREAD = 2;  // We need 2 for our queue
    
    struct HazardRecord {
        std::atomic<T*> hazard_ptr{nullptr};
        char padding[64 - sizeof(std::atomic<T*>)];  // Avoid false sharing
    };
    
    // Global hazard pointer array
    static std::array<std::array<HazardRecord, HAZARDS_PER_THREAD>, MAX_THREADS> hazards;
    
    // Thread-local storage for thread ID
    static thread_local size_t thread_id;
    static std::atomic<size_t> thread_counter;
    
    static size_t get_thread_id() {
        static thread_local bool initialized = false;
        if (!initialized) {
            thread_id = thread_counter.fetch_add(1) % MAX_THREADS;
            initialized = true;
        }
        return thread_id;
    }
    
public:
    // Protect a pointer from deletion
    static void protect(size_t index, T* ptr) {
        size_t tid = get_thread_id();
        hazards[tid][index].hazard_ptr.store(ptr);
    }
    
    // Stop protecting a pointer
    static void unprotect(size_t index) {
        size_t tid = get_thread_id();
        hazards[tid][index].hazard_ptr.store(nullptr);
    }
    
    // Check if a pointer is protected by any thread
    static bool is_protected(T* ptr) {
        for (size_t i = 0; i < MAX_THREADS; ++i) {
            for (size_t j = 0; j < HAZARDS_PER_THREAD; ++j) {
                if (hazards[i][j].hazard_ptr.load() == ptr) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // Safe delete: only delete if not protected
    static bool safe_delete(T* ptr) {
        if (!is_protected(ptr)) {
            delete ptr;
            return true;
        }
        return false;
    }
    
    static void show_hazard_status() {
        std::cout << "=== Hazard Pointer Status ===" << std::endl;
        for (size_t i = 0; i < MAX_THREADS; ++i) {
            bool has_hazards = false;
            for (size_t j = 0; j < HAZARDS_PER_THREAD; ++j) {
                T* ptr = hazards[i][j].hazard_ptr.load();
                if (ptr != nullptr) {
                    if (!has_hazards) {
                        std::cout << "Thread " << i << ": ";
                        has_hazards = true;
                    }
                    std::cout << "hazard[" << j << "]=" << ptr << " ";
                }
            }
            if (has_hazards) std::cout << std::endl;
        }
    }
};

// Static member definitions
template<typename T>
std::array<std::array<typename SimpleHazardPointers<T>::HazardRecord, SimpleHazardPointers<T>::HAZARDS_PER_THREAD>, SimpleHazardPointers<T>::MAX_THREADS> 
SimpleHazardPointers<T>::hazards;

template<typename T>
thread_local size_t SimpleHazardPointers<T>::thread_id = 0;

template<typename T>
std::atomic<size_t> SimpleHazardPointers<T>::thread_counter{0};

// Now our safe lock-free queue!
template<typename T>
class SafeLockFreeQueue {
private:
    struct Node {
        std::atomic<T*> data;
        std::atomic<Node*> next;
        
        Node() : data(nullptr), next(nullptr) {}
    };
    
    using HazardPtr = SimpleHazardPointers<Node>;
    
    std::atomic<Node*> head;
    std::atomic<Node*> tail;
    
public:
    SafeLockFreeQueue() {
        Node* dummy = new Node();
        head.store(dummy);
        tail.store(dummy);
    }
    
    ~SafeLockFreeQueue() {
        // Clean up remaining nodes
        Node* current = head.load();
        while (current) {
            Node* next = current->next.load();
            T* data = current->data.load();
            if (data) delete data;
            delete current;
            current = next;
        }
    }
    
    void enqueue(T item) {
        Node* new_node = new Node();
        T* data = new T(std::move(item));
        new_node->data.store(data);
        
        while (true) {
            Node* last = tail.load();
            HazardPtr::protect(0, last);  // 🛡️ PROTECT the tail
            
            // Verify tail didn't change while we were protecting it
            if (last != tail.load()) {
                HazardPtr::unprotect(0);
                continue;  // Tail changed, try again
            }
            
            Node* next = last->next.load();
            
            if (last == tail.load()) {  // Double-check consistency
                if (next == nullptr) {
                    // Try to link new node
                    if (last->next.compare_exchange_weak(next, new_node)) {
                        tail.compare_exchange_weak(last, new_node);
                        HazardPtr::unprotect(0);  // 🔓 UNPROTECT
                        std::cout << "Thread " << std::this_thread::get_id() 
                                  << " enqueued: " << item << std::endl;
                        return;
                    }
                } else {
                    // Help advance tail
                    tail.compare_exchange_weak(last, next);
                }
            }
            
            HazardPtr::unprotect(0);  // 🔓 UNPROTECT before next iteration
        }
    }
    
    bool dequeue(T& result) {
        while (true) {
            Node* first = head.load();
            HazardPtr::protect(0, first);  // 🛡️ PROTECT head
            
            // Verify head didn't change
            if (first != head.load()) {
                HazardPtr::unprotect(0);
                continue;
            }
            
            Node* last = tail.load();
            Node* next = first->next.load();
            HazardPtr::protect(1, next);   // 🛡️ PROTECT next
            
            // Double-check consistency
            if (first != head.load()) {
                HazardPtr::unprotect(0);
                HazardPtr::unprotect(1);
                continue;
            }
            
            if (first == last) {
                if (next == nullptr) {
                    // Queue is empty
                    HazardPtr::unprotect(0);
                    HazardPtr::unprotect(1);
                    return false;
                }
                // Help advance tail
                tail.compare_exchange_weak(last, next);
            } else {
                if (next == nullptr) {
                    // Shouldn't happen, try again
                    HazardPtr::unprotect(0);
                    HazardPtr::unprotect(1);
                    continue;
                }
                
                // Read data
                T* data = next->data.load();
                if (data == nullptr) {
                    HazardPtr::unprotect(0);
                    HazardPtr::unprotect(1);
                    continue;
                }
                
                // Try to advance head
                if (head.compare_exchange_weak(first, next)) {
                    result = *data;
                    delete data;
                    next->data.store(nullptr);
                    
                    HazardPtr::unprotect(0);  // 🔓 UNPROTECT
                    HazardPtr::unprotect(1);
                    
                    std::cout << "Thread " << std::this_thread::get_id() 
                              << " dequeued: " << result << std::endl;
                    
                    // NOW WE CAN SAFELY TRY TO DELETE THE OLD HEAD!
                    if (!HazardPtr::safe_delete(first)) {
                        std::cout << "  (Node " << first << " is protected, not deleted)" << std::endl;
                    } else {
                        std::cout << "  (Node " << first << " safely deleted)" << std::endl;
                    }
                    
                    return true;
                }
            }
            
            HazardPtr::unprotect(0);  // 🔓 UNPROTECT before next iteration
            HazardPtr::unprotect(1);
        }
    }
    
    bool empty() const {
        Node* first = head.load();
        Node* last = tail.load();
        return (first == last) && (first->next.load() == nullptr);
    }
};

void demonstrate_hazard_pointers() {
    std::cout << "=== How Hazard Pointers Work ===" << std::endl;
    std::cout << R"(
1. PROTECTION PHASE:
   Before using a pointer, announce: "I'm using this!"
   HazardPtr::protect(index, pointer);

2. VALIDATION PHASE:
   Double-check the pointer is still valid
   if (pointer != atomic_var.load()) { /* pointer changed, retry */ }

3. SAFE USAGE PHASE:
   Now it's safe to dereference the pointer
   pointer->some_field.load();

4. CLEANUP PHASE:
   Announce: "I'm done with this"
   HazardPtr::unprotect(index);

5. DELETION PHASE:
   Before deleting, check if anyone is using it
   if (!HazardPtr::is_protected(pointer)) {
       delete pointer;  // Safe!
   }

The key insight: Hazard pointers create a "grace period" where
memory won't be deleted while someone might still be using it.
)" << std::endl;
}

void test_safe_queue() {
    SafeLockFreeQueue<int> queue;
    
    const int num_threads = 4;
    const int operations_per_thread = 5;
    
    std::vector<std::thread> threads;
    
    std::cout << "\n=== Testing Safe Lock-Free Queue ===" << std::endl;
    
    // Mixed producer-consumer threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&queue, i, operations_per_thread]() {
            // Each thread both produces and consumes
            for (int j = 0; j < operations_per_thread; ++j) {
                // Produce
                int value = i * 100 + j;
                queue.enqueue(value);
                
                // Small delay
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                
                // Try to consume
                int consumed;
                if (queue.dequeue(consumed)) {
                    // Successfully consumed something
                }
                
                // Show hazard pointer status occasionally
                if (j % 2 == 0) {
                    SimpleHazardPointers<SafeLockFreeQueue<int>::Node>::show_hazard_status();
                }
                
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "\n=== Final Status ===" << std::endl;
    std::cout << "Queue empty: " << (queue.empty() ? "Yes" : "No") << std::endl;
    
    // Clean up remaining items
    int remaining = 0;
    int value;
    while (queue.dequeue(value)) {
        remaining++;
    }
    std::cout << "Remaining items dequeued: " << remaining << std::endl;
}

int main() {
    demonstrate_hazard_pointers();
    test_safe_queue();
    
    std::cout << "\n🎉 SUCCESS! We now have a memory-safe lock-free queue!" << std::endl;
    
    return 0;
}