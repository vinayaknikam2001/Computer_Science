#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;
using namespace std::chrono;
#define MAX_TESTS 10000000
#define MAX_T_CNT 4
    
template <typename T>
class SimpleQ
{
    private:
    std::list<lli> m_que;
    std::mutex mtx;
    public:

    SimpleQ ()
    {
    }

    void enqueue (T data)
    {
        mtx.lock();
        m_que.push_back(data);
        mtx.unlock();
    }

    bool dequeue (T& retVal)
    {
        mtx.lock();
        if (!m_que.empty())
        {
            retVal = m_que.front();
            m_que.pop_front();
            mtx.unlock();
            return true;
        }
        mtx.unlock();
        return false;
    }

};

SimpleQ<lli> q;

std::mutex m1;
void insertQ(lli st, lli end)
{
    for (lli i=st; i<=end; ++i)
    {
        q.enqueue(i);
    }
}

static lli iCnt = 0;
void removeQ()
{
    while (1)
    {
        lli iVal;
        if (q.dequeue(iVal)) {
            m1.lock();
            ++iCnt;
            if (iCnt == MAX_TESTS*MAX_T_CNT) {
                m1.unlock();
                return;
            }
            m1.unlock();
        }
        else if (iCnt == MAX_TESTS*MAX_T_CNT)
        {
            return;
        }
    }
}
    
int main()
{
    cout << "Start" << endl;
    auto startTime = std::chrono::high_resolution_clock::now();
    std::thread t1(insertQ, 1, MAX_TESTS);
    std::thread t2(insertQ, 1, MAX_TESTS);
    std::thread t3(insertQ, 1, MAX_TESTS);
    std::thread t4(insertQ, 1, MAX_TESTS);
    
    std::thread t5(removeQ);
    std::thread t6(removeQ);
    std::thread t7(removeQ);
    std::thread t8(removeQ);


    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);
    cout<<"Sec : "<<duration.count()/(1e6)<<endl;
    cout << "Exit" << endl;
    return 0;
}