getNodeHeight//{ Driver Code Starts
//

#include <bits/stdc++.h>
#define MAXN 2000
using namespace std;

struct Node
{
    int data, height;
    Node *left, *right;
    
    Node(int x)
    {
        data=x;
        left=right=NULL;
        height=1;
    }
};

bool isBST(Node *n, int lower, int upper)
{
	if(!n) return 1;
	if( n->data <= lower || n->data >= upper ) return 0;
	return isBST(n->left, lower, n->data) && isBST(n->right, n->data, upper) ;
}

pair<int,bool> isBalanced(Node* n)
{
	if(!n) return pair<int,bool> (0,1);

	pair<int,bool> l = isBalanced(n->left);
	pair<int,bool> r = isBalanced(n->right);

	if( abs(l.first - r.first) > 1 ) return pair<int,bool> (0,0);

	return pair<int,bool> ( 1 + max(l.first , r.first) , l.second && r.second );
}

bool isBalancedBST(Node* root)
{
	if( !isBST(root, INT_MIN, INT_MAX) )
		cout<< "BST voilated, inorder traversal : ";

	else if ( ! isBalanced(root).second )
		cout<< "Unbalanced BST, inorder traversal : ";

	else return 1;
	return 0;
}

void printInorder(Node* n)
{
	if(!n) return;
	printInorder(n->left);
	cout<< n->data << " ";
	printInorder(n->right);
}


// } Driver Code Ends

/* The structure of the Node is
struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;
};
*/

class Solution{
    
    int getBalanceFactor(Node *pNode)
    {
        int iLeftHeight = p->left ? p->left->height : 0;
        int iRightHeight = p->right ? p->right->height : 0;
        
        return (iLeftHeight - iRightHeight);
    }
    
    int getNodeHeight(Node *pNode)
    {
        int iLeftHeight = p->left ? p->left->height : 0;
        int iRightHeight = p->right ? p->right->height : 0;
        
        return (max(iLeftHeight, iRightHeight) + 1);
    }
    
    Node* LLRotation(Node *pNode)
    {
        Node *pLNode = pNode->left;
        Node *pLRNode = pLNode->right;
        
        pLNode->right = pNode;
        pNode->left = pLRNode;
        
        //Always calulate height from the bottom nodes to top nodes
        //First calculating pNode cause pNode is own right of pLNode.
        pNode->height = getNodeHeight(pNode);
        pLNode->height = getNodeHeight(pLNode);
        
        
        
        return pLNode;
    }
    
    Node* LRRotation(Node *pNode)
    {
        Node *pLNode = pNode->left;
        Node *pLRNode = pLNode->right;
        
        pNode->left = pLRNode->left;
        pLNode->right = pLRNode->right;
        
        pLRNode->left = pLNode;
        pLRNode->right = pNode;
        
        pNode->height = getNodeHeight(pNode);
        pLNode->height = getNodeHeight(pLNode);
        pLRNode->height = getNodeHeight(pLRNode);
        
        return pLRNode;
    }
  public:
  
    // void insertAVL(Node *pRoot, Node* pNode)
    // {
    //     if (pRoot->left->data)
    // }
    
    /*You are required to complete this method */
    Node* insertToAVL(Node* node, int data)
    {
        if (NULL == node)
        {
            Node *pNode = new Node(data);
            return pNode;
        }
        if (data < node->data)
        {
            node->left = insertToAVL(node->left, data);    
        }
        if (data > node->data)
        {
            node->right = insertToAVL(node->left, data);
        }
        
        node->height = getNodeHeight(node);
        
        if (getBalanceFactor(node) == 2 && getBalanceFactor(node->left) == 1)
        {
            LLRotation(node);
        }
        else if (getBalanceFactor(node) == 2 && getBalanceFactor(node->right) == -1)
        {
            LRRotation(node);
        }
        else if (getBalanceFactor(node) == -2 && getBalanceFactor(node->right) == -1)
        {
            RRRotation(node);
        }
        else if (getBalanceFactor(node) == -2 && getBalanceFactor(node->left) == 1)
        {
            RLRotation(node);
        }
        
        return node;
    }
};


//{ Driver Code Starts.

int main()
{
	int ip[MAXN];
    
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        
        for(int i=0; i<n; i++)
            cin>> ip[i];
        
        Node* root = NULL;
        Solution obj;
        for(int i=0; i<n; i++)
        {
            root = obj.insertToAVL( root, ip[i] );
            
            if ( ! isBalancedBST(root) )
                break;
        }
        
        printInorder(root);
        cout<< endl;
    
cout << "~" << "\n";
}
    return 0;
}
// } Driver Code Ends