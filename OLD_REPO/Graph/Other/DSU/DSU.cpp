#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;

/*
DSU:
It is particularly useful in dynamic connectivity problems, where edges are added at runtime, 
and you need to efficiently check if two nodes are connected.

Important !: 
Graph Edge Deletion-> Standard Disjoint Set does NOT support edge deletion efficiently. 
You’d need other approaches like rollback techniques or dynamic 
connectivity data structures (e.g., Link/Cut Trees).
*/

class DSU
{
    private:
    vector<int> vRank, vParent, vSize;

    public:

    DSU(int n)
    {
        vRank.resize(n+1, 0);
        vSize.resize(n+1, 1);
        vParent.resize(n+1, 0);
        for (int i=0; i<=n; ++i)
        {
            vParent[i] = i;
        }
    }

    int findUParent(int iNode)
    {
        if (vParent[iNode] == iNode) {
            return iNode;
        }

        return vParent[iNode] = findUParent(vParent[iNode]);
    }

    /*
    1> Take ultimate parent of both nodes check if it's equal then return else goto step 2.
    2> If there ultimate parent's are not equal then, check if rank of node1's ultimate parent is strictly lesser than node2's 
       ultimate parent if true then make (attach) node1's ultimate parent to node2's ultimate parent.
    3> In step 3 do the opposite of step 2.
    4> Step 4 if both have same rank then make(attach) node2's ultimate parent to node1's ultimate
       parent and increase the rank of node1's ultimate parent. 
    */
    void unionByRank(int iNode1, int iNode2)
    {
        int iUParent1 = findUParent(iNode1);
        int iUParent2 = findUParent(iNode2);
        
        if (iUParent1 == iUParent2) {
            return;
        }
        if (vRank[iUParent1] < vRank[iUParent2]) {
            vParent[iUParent1] = iUParent2;
        }
        else if (vRank[iUParent2] < vRank[iUParent1]) {
            vParent[iUParent2] = iUParent1;
        }
        else {
            vParent[iUParent2] = iUParent1;
            ++vRank[iUParent1];
        }
        cout<< "\nParent: ";
        for (auto iVal:vParent) { cout << iVal << " "; }
        cout<<"\n";
    }

    /*
    1> Take ultimate parent of both nodes check if it's equal then return else goto step 2.
    2> If ultimate parent's are not equal then we check if vSize of node1's ultimate parent is lesser then node2's ultimate
       parent if true then make (attach) node1's ultimate parent to node2's ultimate parent. And increase size of node2's ultimate parent
       by size of node1's ultimate parent.
    3> In step 3 do the opposite of step 2.
    */
    void unionBySize(int iNode1, int iNode2)
    {
        int iUParent1 = findUParent(iNode1);
        int iUParent2 = findUParent(iNode2);
        
        if (iUParent1 == iUParent2) {
            return;
        }
        if (vSize[iUParent1] < vSize[iUParent2]) {
            vParent[iUParent1] = iUParent2;
            vSize[iUParent2] += vSize[iUParent1];
        }
        else {
            vParent[iUParent2] = iUParent1;
            vSize[iUParent1] += vSize[iUParent2];
        }
        cout<< "\nParent: ";
        for (auto iVal:vParent) { cout << iVal << " "; }
        cout<<"\n";
    } 


    bool isSameComponent(int iNode1, int iNode2) 
    {
        bool bRetVal = false;
        if (findUParent(iNode1) == findUParent(iNode2)) {
            cout << "Nodes "<< iNode1 <<" & " << iNode2 << " are in same component:)\n";
            bRetVal = true;
        }
        else {
            cout << "Nodes "<< iNode1 <<" & " << iNode2 << " are in diffrent component!\n";
            bRetVal = false;
        }
        return bRetVal;
    }

};
    
int main()
{
    
    DSU dsuByRank(7), dsuBySize(7);
    cout << "\nTest case 1 Union By Rank*************************************\n\n";
    dsuByRank.unionByRank(1, 2);
    dsuByRank.unionByRank(2, 3);
    dsuByRank.unionByRank(4, 5);
    dsuByRank.unionByRank(6, 7);
    dsuByRank.unionByRank(5, 6);

    dsuByRank.isSameComponent(3, 7);
    cout << "Connected 3 & 7:)\n";
    dsuByRank.unionByRank(3, 7);

    dsuByRank.isSameComponent(3, 7);


    
    cout << "\n\n\nTest case 1 Union By Size*************************************\n\n";
    dsuBySize.unionByRank(1, 2);
    dsuBySize.unionByRank(2, 3);
    dsuBySize.unionByRank(4, 5);
    dsuBySize.unionByRank(6, 7);
    dsuBySize.unionByRank(5, 6);

    dsuBySize.isSameComponent(3, 7);
    cout << "Connected 3 & 7:)\n";
    dsuBySize.unionByRank(3, 7);

    dsuBySize.isSameComponent(3, 7);


    
    return 0;
}