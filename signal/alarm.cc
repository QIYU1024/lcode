#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    int count = 0;
    alarm(1); //1s后向该进程发送SIGALRM信号，收到该信号默认行为是终止进程
    while(1)
    {
        cout << count++ << endl;
    }
    return 0;
}