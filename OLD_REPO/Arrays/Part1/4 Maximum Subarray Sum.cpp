//https://www.codingninjas.com/codestudio/problems/630526?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0
//Self Solved

/* Mistakes
	Missed a test case because of not using long long int
*/


/*
SC = O(1)
TC = O(N)
*/
#include <bits/stdc++.h> 
using namespace std;

long long maxSubarraySum(int arr[], int n)
{
    long long int crntSum = 0, mxSum = 0, maxi=0;
    for(int i=0; i<n; i++)
    {
        crntSum += arr[i];
        maxi = max(crntSum, maxi);
        if(crntSum < 0) crntSum = 0;
    }
    
    if(maxi > 0)
        return maxi;
	/*Note:- here we have returned 0 cause if my maxsum is -ve then in that case
	we have to consider empty subarray which has sum equal to zero;*/
    return 0;

}