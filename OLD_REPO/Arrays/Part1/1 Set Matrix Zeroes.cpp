//https://www.codingninjas.com/codestudio/problems/set-matrix-zeros_3846774?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=1
//Self Solved

//Instead of using set we can also use simple array to maintain the count.
#include <bits/stdc++.h>
using namespace std;

/*
SC = O(N+M)
TC = O(N*M) + O(N*M) + O(N*M) = O(N*M)
*/


void setZeros(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();

    set<int> ros;
    set<int> cos;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(matrix[i][j] == 0)
            {
                ros.insert(i); cos.insert(j);
            }
                
        }
    }

    for(int i:ros)
    {
        for(int j=0; j<m; j++)
            matrix[i][j]=0;
    }

    for(int i:cos)
    {
        for(int j=0; j<n; j++)
            matrix[j][i]=0;
    }


}