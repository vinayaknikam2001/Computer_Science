// LeetCode Link = https://leetcode.com/problems/network-delay-time/submissions/
#include <bits/stdc++.h>
using namespace std;

class Solution {

public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) 
    {
        //Constructing graph [s]
        vector<vector<pair<int, int>>> gGraph(n+1);
        for (auto &vEdge:times)
        {
            int iSrc = vEdge[0], iDest = vEdge[1], iWet = vEdge[2];
            gGraph[iSrc].push_back({iDest ,iWet});
        }
        //Constructing graph [e]

        vector<int> vDist(n+1, INT_MAX);
        //Below greater<> creates a MinHeap & less<> MaxHeap
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> pQueue; 
        pQueue.push({0, k});
        vDist[k] = 0;

        while (!pQueue.empty())
        {
            auto node = pQueue.top();
            pQueue.pop();

            for (auto &adjNode: gGraph[node.second])
            {
                int iNewDist = node.first + adjNode.second;
                if (iNewDist < vDist[adjNode.first])
                {
                    vDist[adjNode.first] = iNewDist;
                    pQueue.push({iNewDist, adjNode.first});
                }
            }
        }
        int iMax = INT_MIN;
        for (int i=1; i < vDist.size(); ++i)
        {
            iMax = max(vDist[i] , iMax);
        }
        return (INT_MAX == iMax) ? -1 : iMax;
    }
};