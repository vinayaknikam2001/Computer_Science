// GFG = Delete a node from a given BST
#include <bits/stdc++.h>
using namespace std;

// Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};


// } Driver Code Ends

class Solution {
  public:
  
    
    Node* minOfRightSubTree(Node *pNode)
    {
        while (pNode && pNode->left)
        {
            pNode = pNode->left;
        }
        return pNode;
    }
    // Function to delete a node from BST.
    Node *deleteNode(Node *root, int X) 
    {
        if (!root)
        {
            return NULL;
        }
        if (X < root->data)
        {
            root->left = deleteNode(root->left, X);
        }
        else if (X > root->data)
        {
            root->right = deleteNode(root->right, X);
        }
        else
        {
            //If the node has only one child [s].
            if (NULL == root->left)
            {
                Node *pNode = root->right; //Even if right node is NULL or not it does not matter.
                delete root;
                return pNode; //Even if right node is NULL or not it does not matter.
            }
            else if (NULL == root->right)
            {
                Node *pNode = root->left;
                delete root;
                return pNode;
            }
            //If the node has only one child [e].
            
            Node *pNode = minOfRightSubTree(root->right);
            root->data = pNode->data;
            root->right = deleteNode(root->right, root->data);
                
        }
        
        return root;
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    getchar();

    while (t--) {
        string s;
        getline(cin, s);
        Node* head = buildTree(s);

        int k;
        cin >> k;
        getchar();

        // Node* kNode = search( head, k );
        Solution obj;
        Node* suc = obj.deleteNode(head, k);

        vector<int> v;
        inorder(suc, v);
        for (auto i : v)
            cout << i << " ";
        cout << endl;

        cout << "~"
             << "\n";
    }

    return 0;
}
// } Driver Code Ends