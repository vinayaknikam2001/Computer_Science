#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long int lli;

lli money = 0;
mutex m1;

void addMoney()
{   
    m1.lock();
    for(lli i=1; i<=1e6; i++)
        money++;
    m1.unlock();
}

int main ()
{
    thread t1(addMoney), t2(addMoney);
    t1.join();
    t2.join();
    cout<<money;
    return 0;
}

// Wrong Output without using mutex
// 140155
// [Done] exited with code=0 in 2.426 seconds


// Correct Output with using mutex
// 2000000
// [Done] exited with code=0 in 3.196 seconds
