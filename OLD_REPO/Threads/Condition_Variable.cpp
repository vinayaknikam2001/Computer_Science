#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;


class BANK
{
private:
    int iBalanceAmt;
    std::mutex mtxBank;
    std::condition_variable cvBalance;

public:
    BANK():iBalanceAmt{1000}{}

    void addMoney(unsigned int iAmt)
    {
        std::unique_lock<mutex> uLock(mtxBank);
        iBalanceAmt += iAmt;
        cout<<"Rupees "<<iAmt<<" is added to your account"<<endl;
        checkBalance();
        cvBalance.notify_one();
    }

    bool isBalance()
    {
        return (iBalanceAmt > 1000) ? true: false;
    }

    void withdrawMoney(unsigned int iAmt)
    {
        std::unique_lock<mutex> uLock(mtxBank);
        auto funcLambda = [&](){return (this->iBalanceAmt > 1000) ? true : false;};
        cvBalance.wait(uLock, funcLambda);
        //cvBalance.wait(uLock, isBalance);
        iBalanceAmt -= iAmt;
        cout<<"Rupees "<<iAmt<<" is removed from your account"<<endl;
        checkBalance();
    }

    unsigned int checkBalance()
    {
        cout<<"Current ACC Balance is:"<<iBalanceAmt<<endl;
        return iBalanceAmt;
    }

};

/*
Ideally it is expected that first money should be added then it should be removed.
If by any chance withdraw money gets called first it will lock the mutex with a unique_lock. Then condtion
variable will check condition if true then it goes ahead otherwise it will unlock unique_lock() and then
wait at that line untill notify is called on same condtion variable. Even if notify called untill the
condition becomes true thread will wait there.
*/
    
int main()
{   
    BANK objBank;
    objBank.checkBalance();
    thread tWithdrawMoney(&BANK::withdrawMoney, &objBank, 500);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    thread tAddMoney(&BANK::addMoney, &objBank, 500);
    

    tAddMoney.join();
    tWithdrawMoney.join();
    objBank.checkBalance();
    return 0;
}