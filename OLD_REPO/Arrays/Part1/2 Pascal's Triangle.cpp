//https://www.codingninjas.com/codestudio/problems/1089580?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=1
//Self Solved

#include <bits/stdc++.h> 
using namespace std;
using lli = long long int;
long long int mod=1e9+7;
typedef long long int lli;


/*
SC = O(N^2)
TC = O(N^2)
*/

vector<vector<long long int>> printPascal(int n) 
{
   vector<vector<lli>> v(n);
   v[0].push_back(1);
   for(int i=1; i<n; i++)
   {    
        for(int j=0; j<=i; j++)
        {
            lli val = 0;
            //This is necessary check
            if(j<i) 
                val += v[i-1][j];
            if((j-1) >= 0 && (j-1) < i)
                val += v[i-1][j-1];
            // if(v[i-1][j] != 0 && (i-1) >0)
            //     val += v[i-1][j];
            // if(v[i-1][j-1] != 0 && (i-1) >0 && (j-1)>0)
            //     val += v[i-1][j-1];
            v[i].push_back(val);
        }
   }
    return v;
}