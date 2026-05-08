#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Singleton
{
private:
    //int iVal;
    static std::mutex singleMutex;
    static Singleton *pObj;

    Singleton() {}
public:

    Singleton(const Singleton &objSingleton) = delete;
    static Singleton* getInstance();
};

Singleton* Singleton::pObj = NULL;
std::mutex Singleton::singleMutex;