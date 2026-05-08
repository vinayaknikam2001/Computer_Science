#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull eveSum(ull start, ull end)
{
    ull sum = 0;
    for(; start <= end; start++)
    {
        if((start&1) == 0)
            sum += start;
    }
    return sum;
}

ull oddSum(ull start, ull end)
{
    ull sum = 0;
    for(; start <= end; start++)
    {
        if(start & 1)
            sum += start;
    }
    return sum;
}

int main ()
{
    ull start = 0, end = 19e8;
    
    auto startTime = chrono::high_resolution_clock::now();    

    //eveSum(start, end);
    thread t1(eveSum, start, end);
    //oddSum(start, end);
    thread t2(oddSum, start, end);

    t1.join();
    t2.join();

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout<<"Sec : "<<duration.count()/(1e6)<<endl;

    return 0;
}

// Output without using thread.
// Sec : 3.85019
// [Done] exited with code=0 in 6.055 seconds

// Output using thread.
// Sec : 1.83443
// [Done] exited with code=0 in 4.298 seconds