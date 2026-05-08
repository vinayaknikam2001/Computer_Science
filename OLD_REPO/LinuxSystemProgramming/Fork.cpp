#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

/*
fork() sys call is used to create a new process. 
The fork() system call duplicates the current process.
The child process is an almost exact copy of the parent process.
The parent and child processes share the same code segment but have separate memory spaces.
Open file descriptors are copied, so both processes can access the same open files.

Returns:
In the Parent Process: fork() returns the process ID (PID) of the child process.
In the Child Process: fork() returns 0.
On Error: If fork() fails (e.g., due to lack of system resources), it returns -1 in the parent process.

In child process it is possible that sometimes PPID can be = 1 because, sometimes parent process may terminate before 
child process is executed completely such process is called orphan process which is acquired by init or systemd.

One more thing "Forked a Process!" will get printed 2^n times where n is number of times the fork() is called.
Is process will get multiplied.
*/

void mainFunc()
{
    fork();
    fork();
    fork();
    cout<<"Forked a Process!"<<endl;
}

int main ()
{
    cout<<"Parent PID: "<<getpid()<<endl;
    int iPID = fork();
    if (0 == iPID)
    {
        cout<<"Inside a child process: "<<getpid()<<" PPID: "<<getppid()<<endl;
    }
    else
    {
        cout<<"Parent Process: "<<getpid()<<endl;   
    }

    return 0;
}