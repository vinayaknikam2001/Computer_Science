#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;

/*
In heap we alway start indexing of internal vector from 1. 
Because formula for {child node  index = iCrnt index * 2} will not work 
if value of iCrnt is 0.
*/
    
class Heap
{
    private:

    vector<int> pQue; //Default value will be INT_MIN.
    public:

    Heap()
    {
        pQue.push_back(INT_MIN); //To use 1 based indexing in our priority queue.
    }

    /*
    Consider this as a sample test case
        (20)
        /  \
    (50)    (40)
   /    \   /
(5)   (10) (30)

    Now to heapify this we have to start from leaf nodes visit each node from the end
    and check if it is a max heap in itself or not  just check 2 child nodes if they are lesser
    if it is max heap then go to next element otherwise swap root (Crnt node) with a child node 
    which has max value among 2 childs and in this way you will heapify all elements in O(n) timecomplexity
    Now as leaf nodes do not have child they will always be max heap. If there are n Nodes in a tree
    then leaf nodes index range from  [floor(n/2) +1 ... n ] so we can skip these leaf nodes in heapify operation.
    */
    /* Function is not in properly working condition has some issues
    static void makeHeap(vector<int>&vList)
    {
        int iCrnt = vList.size() / 2;
        for (; iCrnt >= 0; --iCrnt)
        {
            heapify(vList, iCrnt);
        }
    }
    static void heapify(vector<int>&vList, int iCrnt)
    {
        int iChild = iCrnt*2;
        if (iChild <= vList.size())
        {
            if ((iChild+1) <= vList.size() && (vList[(iChild-1)] < vList[(iChild-1) +1]))
            {
                ++iChild;
            }

            if (vList[(iChild-1)] > vList[(iCrnt-1)])
            {
                swap(vList[(iChild-1)], vList[(iCrnt-1)]);
            }
        }
    }*/

    /*
    To insert element inside a heap first take element and insert it at the end of the tree. 
    i.e., insert the element at the end of the array. (Insert in a way that it should remain a complete binary tree even after insertion.)
    Now next step is to place that element at correct position keep swaping with parent element as long as it's parnet value is lesser.
    */
    bool push(int iVal)
    {
        pQue.push_back(iVal);
        int iCrnt = pQue.size() - 1;

        while (iCrnt > 1)
        {
            int iParent = iCrnt/2;
            if (pQue[iParent] < pQue[iCrnt]) //Check is parent element value is greater, then swap element.
            {
                swap(pQue[iParent], pQue[iCrnt]);
                iCrnt = iParent;
            }
            else 
            { 
                break; 
            }   
        }
        return true;
    }

    /*
    To pop element overwrite first element (root node) with last element and then as last element is copied delete last element 
    and now it's time to place a root node at the correct position. By swapping and comparing crnt node with it's child nodes.abort
    Repeat the process untill crnt element is placed at the correct position.
    */
    int pop()
    {
        int iRetVal = INT_MIN;
        if (pQue.size() > 1)
        {
            iRetVal = pQue[1];
            int iLast = pQue.size() - 1, iCrnt = 1;
            pQue[1] = pQue[iLast];
            pQue.pop_back();

            int iChild = iCrnt * 2;
            while (iChild < iLast) //Check if child element exists or not
            {
                if ((iChild + 1) < iLast //Check If Right element exists or not.
                    && (pQue[iChild + 1] > pQue[iChild])) //And if right element exists,then check for if it's value is greater than left element
                {
                    ++iChild;
                }
                if (pQue[iChild] > pQue[iCrnt]) //Check is child element is greater than Crnt element.
                {
                    swap(pQue[iChild], pQue[iCrnt]);
                    iCrnt = iChild;     //First update current element position as it is swapped.
                    iChild = iChild * 2; //Now update child index to make sure above while() condition checked properly.
                }
                else
                {
                    break;
                }
            }

        }
        return iRetVal;
    }

    //Function to get value of top most element from the queue.
    int top()
    {
        return (pQue.size() > 1) ? pQue[1] : INT_MIN;
    }

    void printHeap()
    {
        cout<<endl;
        for (int i=1; i<pQue.size(); ++i) //As our heap starts from 1 based indexing.
        {
            cout<<pQue[i]<<" ";
        }
    }
};
    
int main()
{

    vector<int> arr = {10, 20, 15, 30, 5, 40, 25};
    Heap::makeHeap(arr);

    for (auto i:arr)
    {
        cout << i<< " ";
    }

    return 0;
}