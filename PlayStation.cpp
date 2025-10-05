#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;

template<typename T>
class HazardPointers
{
    private:
    static constexpr size_t MAX_THREADS = 16;
    static constexpr size_t HAZARD_PER_THREAD = 2;
    static constexpr size_t RETIRE_THRESHOLD = MAX_THREADS * HAZARD_PER_THREAD * 2;
    struct alignas(64) HazardRecord 
    {
        std::atomic<T*> m_ptr;
        //char cPadding[64 - sizeof(std::atomic<T*>)]; //To avoid false sharing between multiple cores of cache.
        HazardRecord(): m_ptr{NULL} {}
    };
    static HazardRecord _arr_Hazards[MAX_THREADS][HAZARD_PER_THREAD];    
    static thread_local size_t __thread_ID;
    static std::atomic<size_t> g_thread_Counter;
    static thread_local std::vector<T*> vec_Retired_List;

    static size_t getThreadID()
    {
        static thread_local bool initialized = false;
        if (!initialized)
        {
            __thread_ID = g_thread_Counter.fetch_add(1) % MAX_THREADS;
            initialized = true;
        }
        return __thread_ID;
    }
    static void scan_And_Delete_Retired_Nodes ()
    {
        if (vec_Retired_List.empty()) {
            return;
        }
        std::vector<T*> vec_Remaining_Nodes;

        for (T* ptr:vec_Retired_List)
        {
            if (!is_Protected(ptr)) {
                delete ptr; ptr = NULL;
            }
            else {
                vec_Remaining_Nodes.push_back(ptr);
            }
        }
        vec_Retired_List.swap(vec_Remaining_Nodes);
    }
    
    public:
    ~HazardPointers ()
    {
        for (T* ptr:vec_Retired_List)
        {
            delete ptr; ptr = NULL;
        }
    }
    static void protect(size_t index, T *ptr)
    {
        size_t t_ID = getThreadID();
        _arr_Hazards[t_ID][index].m_ptr.store(ptr);
    }

    static void unprotect(size_t index)
    {
        size_t t_ID = getThreadID();
        _arr_Hazards[t_ID][index].m_ptr.store(NULL);
    }

    static bool is_Protected(T *ptr)
    {
        for (size_t i=0; i<MAX_THREADS; ++i) {
            for (size_t j=0; j<HAZARD_PER_THREAD; ++j) {
                if (_arr_Hazards[i][j].m_ptr.load() == ptr) {
                    return true;
                }
            }
        }
        return false;
    }

    static bool retire_Node(T *ptr)
    {
        if (NULL == ptr) {
            return false;
        }
        vec_Retired_List.push_back(ptr);

        if (vec_Retired_List.size() >= RETIRE_THRESHOLD)
        {
            scan_And_Delete_Retired_Nodes();
        }
        return true;
    }

};

//Static Member function definitions.
template<typename T>
typename HazardPointers<T>::HazardRecord HazardPointers<T>::_arr_Hazards[HazardPointers<T>::MAX_THREADS][HazardPointers<T>::HAZARD_PER_THREAD];
template<typename T>
thread_local size_t HazardPointers<T>::__thread_ID{0};
template<typename T>
std::atomic<size_t> HazardPointers<T>::g_thread_Counter{0};
template<typename T>
thread_local std::vector<T*> HazardPointers<T>::vec_Retired_List;
// template<typename T>
// constexpr size_t HazardPointers<T>::MAX_THREADS{16};
// template<typename T>
// constexpr size_t HazardPointers<T>::HAZARD_PER_THREAD{2};
// template<typename T>
// constexpr size_t HazardPointers<T>::RETIRE_THRESHOLD{HazardPointers<T>::MAX_THREADS * HazardPointers<T>::HAZARD_PER_THREAD * 2};
///


template <typename T>
class LockFreeQ
{
    private:
    struct Node
    {
        std::atomic<T*> data;
        std::atomic<Node*> next;
        
        Node () : data{NULL}, next{NULL} {}
        Node (T* pData) : data{pData}, next{NULL} {}
        Node (T* pData, Node *pNext) : data{pData}, next{pNext} {}
    };

    std::atomic<Node *> m_head;
    std::atomic<Node *> m_tail;
    using HazardPtr = HazardPointers<Node>;

    public:

    LockFreeQ ()
    {
        Node* dummy = new Node();
        m_head.store(dummy);
        m_tail.store(dummy);
    }
    ~LockFreeQ ()
    {
        Node *pCrntNode = m_head.load();
        while (pCrntNode)
        {
            Node *pNext = pCrntNode->next.load();
            T* pData = pCrntNode->data.load();
            delete pData; pData = NULL;
            delete pCrntNode;
            pCrntNode = pNext;
        }
    }
    LockFreeQ (const LockFreeQ&) = delete;
    LockFreeQ& operator= (const LockFreeQ&) = delete;
    
    bool enqueue (T data)
    {
        Node *pNode = new Node();
        T* pData = new T(std::move(data));
        pNode->data.store(pData);
        while (true)
        {
            Node *pLast = m_tail.load();
            HazardPtr::protect(0, pLast);
            if (m_tail.load() != pLast)
            {
                HazardPtr::unprotect(0);
                continue;
            }
            Node *pNext = pLast->next.load();
            if (m_tail.load() == pLast)
            {
                if (NULL == pNext)
                {
                    if (pLast->next.compare_exchange_weak(pNext, pNode))
                    {
                        m_tail.compare_exchange_weak(pLast, pNode);
                        HazardPtr::unprotect(0);
                        return true;
                    }
                }
                else {
                    m_tail.compare_exchange_weak(pLast, pNext);
                }
            }
            HazardPtr::unprotect(0);
        } 
        return false;
    }

    bool dequeue (T &returnValue)
    {
        while (true)
        {
            Node *pFirst = m_head.load();
            HazardPtr::protect(0, pFirst);
            if (m_head.load() != pFirst)
            {
                HazardPtr::unprotect(0);
                continue;
            }
            Node *pLast = m_tail.load();
            Node *pNext = pFirst->next.load();
            HazardPtr::protect(1, pNext);
            if (m_head.load() != pFirst)
            {
                HazardPtr::unprotect(0);
                HazardPtr::unprotect(1);
                continue;
            }
            if (pFirst == pLast)
            {
                if (NULL == pNext)
                {
                    HazardPtr::unprotect(0);
                    HazardPtr::unprotect(1);
                    return false;
                }
                m_tail.compare_exchange_weak(pLast, pNext);
            }
            else
            {
                if (NULL == pNext)
                {
                    HazardPtr::unprotect(0);
                    HazardPtr::unprotect(1);
                    continue;
                }
                T* data = pNext->data.load();
                if (NULL == data)
                {
                    HazardPtr::unprotect(0);
                    HazardPtr::unprotect(1);
                    continue;    
                }
                if (m_head.compare_exchange_weak(pFirst, pNext))
                {
                    returnValue = *data;
                    delete data;
                    pNext->data.store(NULL);
                    HazardPtr::unprotect(0);
                    HazardPtr::unprotect(1);
                    HazardPtr::retire_Node(pFirst);
                    return true;
                }                                
            }
            HazardPtr::unprotect(0);
            HazardPtr::unprotect(1);
        }
    }

};

LockFreeQ<int> q;

void insertQ(int st, int end)
{
    for (int i=st; i<=end; ++i)
    {
        q.enqueue(i);
    }
}

FILE *pFile = fopen("Out.txt", "w");

std::mutex m1;
void removeQ()
{
    while (1)
    {
        int iVal;
        if (q.dequeue(iVal)) {
            std::unique_lock<std::mutex> ul(m1);
            cout << iVal << endl;
            fprintf(pFile, "%d\n", iVal);
        }
    }
}
    
int main()
{    
    
    std::thread t1(insertQ, 1, 20000);
    std::thread t2(insertQ, 20001, 41000);
    std::thread t3(insertQ, 41001, 60000);
    //std::thread t4(removeQ);
    std::thread t5(removeQ);

    t1.join();
    t2.join();
    t3.join();
    //t4.join();
    t5.join();
    cout << "Exit" << endl;
    fclose(pFile);
    return 0;
}




//

//what if in dequeue one thread is on if (head.compare_exchange_weak(first, next)) // and another thread is using safe_delete but since ptr is protected by other threads it will cause a leak

/*
1> Cannot traverse this Q
2> IsEmpty is not safe completely.
3> Also beyond 16 threads limit it will not work.
4> Some sample examples consider below list and enqueue & dequeue takes place at same time.
(Dummy)->(1)->(Null)
*/