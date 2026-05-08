#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;

/*
0   1  2  3  4
[ 1| 2| 3| 4| 5]
Head = -1  = 0 
Tail = 0   = 0

No Insertion As Both Are Pointing To Zero
Head = 0
Tail = 0

While Deleting when both point to same just reset them to because this means array is empty.
Head = -1
Tail = 0
*/

template <typename T>
class CircularQueue
{
    private:
    T *m_iCicularArr;
    ssize_t iHead, iTail, iCnt;
    const ssize_t iSize;

    inline ssize_t getNext(ssize_t iIndex) { return ((iIndex+1) % iSize); }
    inline void resetQueue() { iHead = iTail = iCnt = 0; }
    public:

    //Deleting some default functions.
    CircularQueue() = delete;
    CircularQueue(const CircularQueue&) = delete;
    CircularQueue& operator=(const CircularQueue&) = delete;

    //Parameterized Constructor
    CircularQueue (const ssize_t iSize) : iSize{iSize}, iHead{0}, iTail{0}, iCnt{0}
    {
        if (0 >= iSize)
        {
            cerr << "CircularQueue size can not be less than or equal to zero!" << endl;
            throw invalid_argument("CircularQueue size can not be less than or equal to zero!");
        }
        m_iCicularArr = new T[iSize];
    }

    //Destructor
    ~CircularQueue()
    {
        if (nullptr != m_iCicularArr)
        {
            delete[] m_iCicularArr;
            m_iCicularArr = nullptr;
        }
    }

    //Inline Functions
    bool isEmpty() const { return (iCnt == 0); }
    bool isFull() const { return (iCnt == iSize); }
    inline ssize_t getCount() const { return iCnt; }
    inline ssize_t getSize() const { return iSize; }

    //Peak the element
    inline bool peak(T &obj) const
    { 
        if (isEmpty())
        {   
            cerr << "Can't Peak. Queue is Empty!" << endl;
            return false;      
        }
        obj = m_iCicularArr[iHead];
        return true;
    }

    //Insert Elements
    bool enqueue(const T &iValue)
    {
        if (nullptr == m_iCicularArr)
        {
            cerr << "Nullptr in Enqueue!" << endl;
            return false;
        }
        if (isFull())
        {
            cout << "Can't Enqueue.Queue is Full!" << endl; 
            return false;
        }
        m_iCicularArr[iTail] = iValue;
        iTail = getNext(iTail);
        ++iCnt;
        return true;
    }

    //Delete Elements
    bool dequeue()
    {
        if (nullptr == m_iCicularArr)
        {
            cerr << "Nullptr in Dequeue!" << endl;
            return false;
        }
        if (isEmpty())
        {
            cerr << "Can't Dequeue.Queue is Empty!" << endl; 
            return false;
        }
        iHead = getNext(iHead);
        --iCnt;
        if (isEmpty())
        {
            resetQueue();
        }
        return true;
    }

    //Print All Elements
    void print ()
    {
        cout << "\nCircular Queue: " <<endl;
        lli iIdx = iHead;
        while (iIdx != iTail)
        {
            cout << m_iCicularArr[iIdx] << " ";
            iIdx = getNext(iIdx);
        }
        cout << endl;
    }
};

    
int main()
{

    CircularQueue<int> obj(5);

    while (true)
    {
        char cChoice;
        cout << "Enter Choice Press e = Enqueue | d = Dequeue | s = ShowAll | p = peak | x = exit" << endl;
        cin >> cChoice;
        switch (cChoice)
        {
        case 'e':
        case 'E':
        {
            int iVal = 0;
            cout << "Enter the element to insert" << endl;
            cin >> iVal;
            obj.enqueue(iVal);
        }break;
        case 'd':
        case 'D':
        {
            obj.dequeue();
        }break;
        case 's':
        case 'S':
        {
            obj.print();
        }break;
        case 'p':
        case 'P':
        {
            int iVal; 
            obj.peak(iVal);
            cout << "Head Element is: " << iVal << endl; 
        }break;
        case 'x':
        {
            cout << "EXIT" << endl;
            //Do nothing;
        }break;
        default:
            break;
        }

        if ('x' == cChoice)
        {
            break;
        }
    }
    
    return 0;
}