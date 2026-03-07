#include "ThreadSafeSingleton.h"
typedef long long int lli;
typedef unsigned long long ull;

Singleton* Singleton::getInstance()
{
    if (Singleton::pObj == NULL)
    {
        Singleton::singleMutex.lock();
        if (Singleton::pObj == NULL)
        {
            Singleton::pObj = new Singleton();
        }
        Singleton::singleMutex.unlock();
    }

    return Singleton::pObj;   
}


// //This is also an example of thread safe singleton design pattern. IF compiler version in C++11 and later.
// class Singleton
// {
// private:

//     Singleton(){}
//     ~Singleton(){}
// public:
//     Singleton(const Singleton &objSingleton) = delete;
//     Singleton operator=(const Singleton &objSingleton) = delete;

//     static Singleton& getInstance() 
//     {
//         static Singleton objSingleton;//In C++ 11 and later local static variable creation is thread safe.
//         return objSingleton;
//     }

// };
    
int main()
{
    Singleton *pObj = Singleton::getInstance();
    Singleton *pObj2 = Singleton::getInstance();

    cout<<"Obj1="<<pObj<<" Obj2="<<pObj2<<" EXIT";
    return 0;
}