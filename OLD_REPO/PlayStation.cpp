#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;
    

#define TEN 10
typedef long long int lli;
typedef unsigned long long ull;

constexpr lli BASE1 = 31, BASE2 = 37, MOD1 = 1e9+7, MOD2 = 1e9+9;

constexpr lli getPower(lli BASE, lli EXP, lli MOD)
{
    lli iRes = 1;
    for (int i=0; i<EXP; ++i)
    {
        iRes = (iRes * BASE) % MOD;
        //cout << iRes << endl;
    }
    //cout << "END \n\n";
    return iRes;
}

constexpr lli POW1 = getPower(BASE1, TEN-1, MOD1), POW2 = getPower(BASE2, TEN-1, MOD2);
    
int main()
{
    lli iRes = 1;
    lli MOD = 1e9 + 7;
    cout << "MyCode" ;
    for (int i=0; i<9; i++)
    {
        iRes = ((lli)31 * (lli)iRes) % MOD;
        cout << iRes << endl;
    }
    
    return 0;
}