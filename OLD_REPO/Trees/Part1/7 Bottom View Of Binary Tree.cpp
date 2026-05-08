// GFG = https://www.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1
// Self solved

#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

class Solution 
{
public:

    vector <int> bottomView(Node *root) 
    {
        vector<int> ans;
        if (root == NULL)
            return ans;
            
        queue<pair<int,Node*>> q;
        map<int, int> mp;
        q.push({0, root});
        
        while (!q.empty())
        {
            auto nodePair = q.front();
            q.pop();
            
            int line = nodePair.first;
            Node *pNode = nodePair.second;
            
            mp[line] = pNode->data;
            
            if (pNode->left != NULL)
                q.push({line-1, pNode->left});
            
            if (pNode->right != NULL)
                q.push({line+1, pNode->right});
        }
        
        for (const auto ele: mp)
        {
            ans.push_back(ele.second);
        }
        return ans;
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    string tc;
    getline(cin, tc);
    t=stoi(tc);
    while(t--)
    {
        string s ,ch;
        getline(cin, s);
        Node* root = buildTree(s);
        Solution ob;
        vector <int> res = ob.bottomView(root);
        for (int i : res) cout << i << " ";
        cout << endl;
    }
    return 0;
}



// } Driver Code Ends