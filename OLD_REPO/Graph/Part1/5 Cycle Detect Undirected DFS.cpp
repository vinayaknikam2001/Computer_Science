#include <bits/stdc++.h>
using namespace std;
// Self Sovled
/*
Remember ...
Corner Case
0<-->1
*/

bool isCycle(int V, vector<int> adj[]) 
{
    vector<bool> vis(V,false);
    for(int i=0; i<V; i++){
        if(!vis[i]) {
            if(DFS(i, adj, vis, -1))
                return true;
        }
    }
    
    return false;
}

bool DFS(int vertex, vector<int> adj[], vector<bool> &vis, int parent)
{
    vis[vertex] = 1;
    
    for(auto node:adj[vertex])
    {
        if(!vis[node]){
            if(DFS(node, adj, vis, vertex))
                return true;
        }
        else if(parent != node) return true;
    }
    return false;
}
