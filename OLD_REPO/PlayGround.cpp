#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;
    
int main()
{
    vector<int> vec(10, 2);
    int *p = &vec[0];
    vec.push_back(3);
    cout << *p <<endl;
    return 0;
}