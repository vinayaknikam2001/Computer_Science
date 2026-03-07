#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <type_traits>

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads = std::thread::hardware_concurrency()) 
        : stop(false) {
        for(size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while(true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { 
                            return stop || !tasks.empty(); 
                        });
                        
                        if(stop && tasks.empty())
                            return;
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    // Submit any callable (function, lambda, member function, etc.)
    template<class F, class... Args>
    auto submit(F&& f, Args&&... args) 
        -> std::future<typename std::invoke_result_t<F, Args...>> {
        
        using return_type = typename std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            
            if(stop)
                throw std::runtime_error("submit on stopped ThreadPool");

            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for(std::thread &worker : workers)
            worker.join();
    }

    // Delete copy constructor and assignment
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

// ==================== DEMO CODE ====================

// Normal C function
int add(int a, int b) {
    std::cout << "Normal function: " << a << " + " << b << std::endl;
    return a + b;
}

// Class with member functions
class Calculator {
public:
    int multiply(int a, int b) {
        std::cout << "Member function: " << a << " * " << b << std::endl;
        return a * b;
    }
    
    static int subtract(int a, int b) {
        std::cout << "Static function: " << a << " - " << b << std::endl;
        return a - b;
    }
};

int main() {
    ThreadPool pool(4);
    std::vector<std::future<int>> results;

    // 1. Normal C function
    results.emplace_back(pool.submit(add, 10, 20));

    // 2. Lambda function
    results.emplace_back(pool.submit([](int x, int y) {
        std::cout << "Lambda function: " << x << " / " << y << std::endl;
        return x / y;
    }, 100, 5));

    // 3. Static member function
    results.emplace_back(pool.submit(&Calculator::subtract, 50, 15));

    // 4. Member function with object
    Calculator calc;
    results.emplace_back(pool.submit(&Calculator::multiply, &calc, 7, 8));

    // 5. Lambda with capture
    int multiplier = 3;
    results.emplace_back(pool.submit([multiplier](int x) {
        std::cout << "Lambda with capture: " << x << " * " << multiplier << std::endl;
        return x * multiplier;
    }, 15));

    // 6. Function pointer
    int (*funcPtr)(int, int) = add;
    results.emplace_back(pool.submit(funcPtr, 5, 7));

    // 7. std::function
    std::function<int(int, int)> func = [](int a, int b) {
        std::cout << "std::function: " << a << " % " << b << std::endl;
        return a % b;
    };
    results.emplace_back(pool.submit(func, 17, 5));

    // Collect results
    std::cout << "\n=== Results ===" << std::endl;
    for(size_t i = 0; i < results.size(); ++i) {
        std::cout << "Result " << i + 1 << ": " << results[i].get() << std::endl;
    }

    return 0;
}