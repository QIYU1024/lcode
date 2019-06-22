//实现前5秒不能被2号信号终止
#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void handler(int signo)
{
    cout << "Cannot be killed by SIGINT for 5 seconds." << endl;
}

int main()
{
    signal(SIGINT, handler); //捕获SIGINT信号
    struct sigaction act = {SIG_DFL};
    int i = 5;
    while(i--)
    {
        sleep(1);
        //Make the process sleep for SECONDS seconds, or until a signal arrives and is not ignored. 
    }
    sigaction(2, &act, NULL); //将对SIGINT信号的处理行为置为默认
    cout << "Can be killed by SIGINT." << endl;
    while(1);
    return 0;
}