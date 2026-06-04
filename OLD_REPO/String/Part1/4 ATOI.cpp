#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define MIN_INT_32 -2147483648
#define MAX_INT_32 2147483648-1
#define DECIMAL 10
class Solution 
{
public:
    int myAtoi(string s) 
    {
        lli iNumber = 0;
        bool bNoStart = false, bNegative = false;
        short iCnt = 0;

        for (int i=0; i<s.size(); ++i)
        {
            if ((s[i] == ' ' || s[i] == '0') && !bNoStart)
            {
                bNoStart = (s[i] == '0');
                continue;
            }

            if ((s[i] == '+' || s[i] == '-') && !bNoStart)
            {
                bNegative = (s[i] == '-');
                bNoStart = true;
                continue;
            }

            short iDigit = (s[i] - '0');
            if (iDigit > 9 || iDigit < 0)
            {
                break;
            }
            cout << iCnt << endl;
            if (iCnt > 11)
            {
                break;
            }
            iNumber = (iNumber * (lli)DECIMAL) + (lli)iDigit;
            ++iCnt;
        }

        iNumber = (bNegative) ? (-1 * iNumber) : iNumber;
        cout << iNumber;
        iNumber = max((lli)MIN_INT_32, iNumber);
        iNumber = min((lli)MAX_INT_32, iNumber);

        return iNumber;
    }
};


int main ()
{
    Solution s;
    s.myAtoi("21474836460");
    return 0;
}