#include <mutex>

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

Singleton* Singleton::pObj;
std::mutex Singleton::singleMutex;