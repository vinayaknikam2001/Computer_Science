#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef unsigned long long ull;
#define USE_CAS 1 //Copy and Swap Idiom...


class String
{
    private:
        char *pcStr;
        ull iSize;

    public:

    String(): pcStr(NULL), iSize(0){}

    /*Below is parameterized constructor we have used const 
    pointer to point to const character array because we don't want to accidentally
    change this value */
    String(const char *const cStr)
    {
        if(cStr)
        {
            this->iSize = strlen(cStr);
            this->pcStr = new char[this->iSize+1];
            strcpy(this->pcStr, cStr);
        }
    }

    /*Below is copy constructor we have const to keep value immutable
    and we have taken it by reference casue otherwise it will again 
    call a copy constructor to create paramenter object which is not there*/
    String(const String &objStr)
    {
        this->iSize = objStr.iSize;
        this->pcStr = new char[objStr.iSize+1];
        strcpy(this->pcStr, objStr.pcStr);
    }

#ifndef USE_CAS
    /*Below is a copy assignment operator*/
    String& operator=(const String &objStr)
    {
        /*We have used below condtion to avoid self assignment
        to avoid doing let's say 
        String s1;
        s1 = s1 //This king of operation...:) 
        below code avoids unnecessary operations in case object is same
        */
        if(this != &objStr)
        {
            if(this->pcStr)
            {
                delete[] pcStr;
                pcStr = NULL;
                this->iSize = objStr.iSize;
                this->pcStr = new char[objStr.iSize+1];
                strcpy(this->pcStr, objStr.pcStr);
            }
        }
        return *this;/*Remember when we have reference type return we have to pass *p i.e., value at  p*/
    }
#else
    /*A better replacement for above copy assignment operator is one technique CAS
    (Copy And Swap) idiom this is safer and gracefull way to do things remeber when 
    we pass this String i.e., s1 = s2 s3 willbe parameter to below func and it is passed 
    by value which actually calls a copy constructor on paramter object and then
    we simply swap that value so original RValue remains unchanged*/
    String& operator=(String objStr) 
    {
        swapStr(*this, objStr);
        return *this;
    }
#endif

   void swapStr(String &s1, String &s2)
   {
        swap(s1.iSize, s2.iSize);
        swap(s1.pcStr, s2.pcStr);
   }

   /*Writing operator overloading to concatenate to String class*/
   String operator+(const String& s1)
   {
        String sRes;
        sRes.iSize = this->iSize + s1.iSize;
        sRes.pcStr = new char[sRes.iSize + 1];
        snprintf(sRes.pcStr, sRes.iSize+1, "%s%s", this->pcStr, s1.pcStr);
        return sRes;
   }


    ~String()
    {
        if(this->pcStr)
        {
            delete[] this->pcStr;
            this->pcStr = NULL;
            iSize = 0;
        }
    }
    friend ostream& operator<<(ostream&, const String&);
    friend istream& operator>>(istream&, const String&);
};

/*Now to overload cin and cout we have to declare functions outside a class cause
there are 2 objects in below statement one is ostream object and other is our String object
cout<<str; // soif we want we have to make change in ostream's class which is not good solution.
so best is to declare outside class but as a friend function...:)
as it is not member of any class we have to pass ostream as parameter*/
ostream& operator<<(ostream &out, const String &objStr)
{
    out<<objStr.pcStr; //As cout knows already how to print a charater pointer.
    return out;  
    /*Always remeber to this out to support method chaining Ex.
    cout<<s1<<s2<<s3; //this kind of situation*/
}

istream& operator>>(istream& in, const String &objStr)
{
    in>>objStr.pcStr;
    return in;
}
    
int main()
{
    
    String str1; //A default constructor.
    
    String str2("C++"); //Parameterized constructor.
    cout<<"Con param 1 "<<str2<<endl;
    String str3 = "Java";//Parameterized constructor.
    cout<<"Con param 2 "<<str3<<endl;

    
    String str4 = str2; //Copy constructor.
    cout<<"Con copy 1 "<<str4<<endl;
    String str5(str3);
    cout<<"Con copy 1 "<<str5<<endl;

    String str6 = "Javascript";
    String str7 = str6;
    cout<<"Before copy assignment ops "<<str6<<endl;
    str6  = str2;   //Copy assignment operator
    cout<<"Before copy assignment ops "<<str6<<endl;

    cout<<"All "<<str2<<str3<<str7 <<endl;

    cout << (str2+str3) << endl;
    /*
    Remeber std::move assignment and constructor are diffrent;
    String s1 = std::move(s2); //This is move constructor..
    String s3;
    s3 = std::move(s4);   //This is move assignment operator
    */
    return 0;
}