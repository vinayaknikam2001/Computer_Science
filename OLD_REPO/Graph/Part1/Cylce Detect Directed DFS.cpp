//Self Solved 
// Self 
#include <bits/stdc++.h>
using namespace std;
/*
Remeber...
Corner Case
0->1<-2
*/

bool isCyclic(int V, vector<int> adj[]) 
    {
        vector<bool> vis(V,false), recStack(V,false);
        for(int i=0; i<V; i++)
        {
            if(!vis[i]){
                if(DFS(adj, i, vis, recStack)) return true;
            }
        } 
        
        return false;
    }
    
    
    bool DFS(vector<int> adj[], int &vertex, vector<bool>&vis, vector<bool>&recStack)
    {
        vis[vertex] = 1;
        recStack[vertex] = 1;
        
        bool ans = false;
        for(auto node:adj[vertex]){
            if(!vis[node]){
                ans |= DFS(adj, node, vis, recStack);
            }
            else if(recStack[node]) return true;
        }
        
        recStack[vertex] = 0;
        return ans;
    }
