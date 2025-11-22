#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;


    lli calculateForLast(lli num)
    {
        lli numC = num;
    }

    lli numWithoutZeroes(lli n)
    {

        lli iRes = 0, iDigit = 0;
        lli num = n;
        bool bIsMedZero = false;

        iDigit = ((n/10) > 0) ? 9 : n%10;
        if ((n/10) <= 0) iRes += iDigit;
        while ((n/10) > 0)
        {
            // lli iDigit = n%10;
            // if (0 != iDigit) 
            // {
            //     iRes = (iDigit * iDecCnt) + iRes;
            //     iDecCnt *=  10;
            // }
            if (num != n)
            {
                bIsMedZero = (n%10 == 0); 
            }
            iRes = (iDigit) + iRes;
            n /= 10;
            iDigit *= 9;
        }

        iRes = (bIsMedZero) ? iRes : (iRes + calculateForLast(num));

        return iRes;
    }
    
int main()
{
    

    cout << numWithoutZeroes(450);
    
    return 0;
}