//https://www.codingninjas.com/codestudio/problems/1115474?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=0
//Referenced
/*Here min product also stores largest value but in negative format. That's why we are swapping. If -ve elements are present even times then,
	swap will give +ve result and not matter what we are storing maximum of ans variable.
	Corner Cases:
	{3, 2, -2}; {3, 2, -2, -3}; {2, 3, -5, 3, 5};
*/
#include <bits/stdc++.h> 
using namespace std;

int maximumProduct(vector<int> &arr, int n)
{
	int ans = arr[0], maxProd = arr[0], minProd = arr[0];

	for(int i=1; i<n; i++)
	{
		if(arr[i] < 0)
			swap(maxProd, minProd);
		maxProd = max(arr[i], arr[i] * maxProd);
		minProd = min(arr[i], arr[i] * minProd);
		ans = max(ans, maxProd);
	}

    return ans;
}
