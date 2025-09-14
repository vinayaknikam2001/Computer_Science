#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;


/*
int *m_piArr = new int(10);   //Creates only one int element & assigns value 10 to it. 
int *m_piArr = new int[10];   //Creates array of 10 elements & value in that could be anything.
int *m_piArr = new int[10](); //Creates array of 10 elements & Sets all values to zero.
                               but you can't pass parameter inside () gives compilation error.
There is difference in above 3 Syntax.
~Destructor function can not have parameters compilation error.
*/
class CircularQ
{
    private:
        lli *m_piArr;
        lli m_iFront, m_iRear;
        size_t m_iSize, m_iCnt;
        inline size_t getNext(size_t iIndex) { return ((iIndex + 1) % m_iSize); }

    public:


    //Default constructor.
    CircularQ() = delete;
    CircularQ(const CircularQ&) = delete;
    CircularQ& operator=(const CircularQ&) = delete;

    //Parameterized constructor.
    explicit CircularQ(size_t iSize) : m_piArr{new lli[iSize]},
             m_iFront {-1}, m_iRear{-1}, m_iSize{iSize}, m_iCnt{0}{}

    //Destructor.
    ~CircularQ()
    {
        if (m_piArr)
        {
            delete[] m_piArr;
            m_piArr = NULL;
        }
    }
    inline bool isEmpty() { return (0 == m_iCnt); }
    inline bool isFull() { return (m_iSize == m_iCnt); }
    inline size_t getCount() { return m_iCnt; }
    inline size_t getSize() { return m_iSize; }
    inline lli peak() { return (isEmpty()) ? -1 : m_piArr[m_iFront]; }
    
    void print()
    {
        if (isEmpty()) 
        {
            cout << "CircularQ is Empty!" << endl;
            return;
        }
        cout << "CircularQ : ";
        lli i = m_iFront;
        while (i!=m_iRear)
        {
            cout << m_piArr[i] << " ";
            i = getNext(i);
        }
        cout << m_piArr[i];
        cout << endl;
    }

    bool enqueue(lli iVal)
    {
        if (isFull()) 
        {
            cout << "Can not insert CircularQ is full!" << endl;
            return false;
        }
        if (isEmpty()) { m_iFront = m_iRear = 0; }
        else { m_iRear = getNext(m_iRear); }

        m_piArr[m_iRear] = iVal;
        ++m_iCnt;
        cout << "Enqueued in CircularQ." << endl;
        return true;
    }

    bool dequeue()
    {
        if (isEmpty())
        {
            cout << "Can not remove CircularQ is empty!" << endl;
            return false;
        }
        if (1 == getCount()) { m_iFront = m_iRear = -1; }
        else { m_iFront = getNext(m_iFront); }
        --m_iCnt;
        cout << "Dequeued from CircularQ." << endl;
        return true;
    }

};
    
    
int main()
{
    CircularQ q(5);
    while (true)
    {
        short iVal = -1;
        cout << "Enter choice ->" << endl;
        cin >> iVal;
        switch (iVal)
        {
            case 1 : 
            {
                lli iValue;
                cout << "Insert ->" <<endl;
                cin >> iValue;
                q.enqueue(iValue);
            }break;
            case 2:
            {
                lli iValue = q.peak();
                q.dequeue();
                cout << "Removed ->" << iValue << endl;
            }break;
            case 3:
            {
                q.print();
            }break;
            case 4:
            {
                cout << "Peak ->" << q.peak() <<endl;
            }break;
            default:
            { exit; }
        }
    }
    return 0;
}