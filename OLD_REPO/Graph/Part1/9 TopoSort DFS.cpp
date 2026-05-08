// Code studio = https://www.codingninjas.com/studio/problems/982938?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTabValue=PROBLEM
// Self  Solved...
// Self 
#include <bits/stdc++.h>
using namespace std;

void DFS (vector<vector<int>> &GList, bool *bVis, stack<int> &st,
         int node)
{
    bVis[node] = true;
    for (int vertex : GList[node])
    {
        if (!bVis[vertex])
            DFS(GList, bVis, st, vertex);
    }
    st.push(node);
}

vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e)  
{
    vector<vector<int>> GList(v);

    for (int i=0; i<e; i++)
    {
        int src = edges[i][0];
        int dst = edges[i][1];
        GList[src].push_back(dst);
    }
    vector<int> topoSort;
    bool bVis[v] = {0};
    stack<int> st;

    for (int i=0; i<v; i++)
    {
        if (!bVis[i])
            DFS(GList, bVis, st, i);
    }
    
    
    while(!st.empty())
    {
        topoSort.push_back(st.top());
        st.pop();
    }

    return topoSort;

}