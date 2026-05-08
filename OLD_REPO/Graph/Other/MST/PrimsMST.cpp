//GFG Link = https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1


//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

class Solution {
  public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) 
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pQ;
        vector<bool> vVisited(V, false);
        
        pQ.push({0,0});
        int iSum = 0;
        
        while (!pQ.empty())
        {
            auto it = pQ.top();
            pQ.pop();
            int iWeight = it.first;
            int iNode = it.second;
            
            if (vVisited[iNode]) 
            {
                continue;
            }
            //Mark element visited when you found a node with least weight only
            vVisited[iNode] = true;
            iSum += iWeight;
            
            for (auto &conNode:adj[iNode])
            {
                int iCNode = conNode[0];
                int iCWeight = conNode[1];
                if (!vVisited[iCNode])
                {
                    /*
                    Don't mark element visited cause we don't know it is part of MST or not we 
                    have to select node with least weight.This is a diffrence in prims algo and
                    a normal BFS in normal BFS we mark visited when we push node inside Q to avoid duplicate 
                    nodes from pushing inside a Q.
                    */
                    pQ.push({iCWeight, iCNode});
                }
            }
            
        }
        
        return iSum;
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i = 0;
        while (i++ < E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1, t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }

        Solution obj;
        cout << obj.spanningTree(V, adj) << "\n";

        cout << "~"
             << "\n";
    }

    return 0;
}

// } Driver Code Ends