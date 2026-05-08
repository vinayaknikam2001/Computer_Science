// GFG Link = https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1
// Self Solved

//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution {
  public:
  
  
    void DFS(vector<int> adj[], bool bVisited[], vector<int> &ans, int node)
    {
        
        bVisited[node] = true;
        ans.push_back(node);
        for (auto i:adj[node])
        {
            if (!bVisited[i])
                DFS(adj, bVisited, ans, i);
        }
    }
    
    // Function to return a list containing the DFS traversal of the graph.
    vector<int> dfsOfGraph(int V, vector<int> adj[]) 
    {
        vector<int> ans;
        bool bVisited[V] = {0};
        
        DFS(adj, bVisited, ans, 0);
        return ans;
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int V, E;
        cin >> V >> E;

        vector<int> adj[V];

        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // string s1;
        // cin>>s1;
        Solution obj;
        vector<int> ans = obj.dfsOfGraph(V, adj);
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
// } Driver Code Ends