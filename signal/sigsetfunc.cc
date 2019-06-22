//练习操作sigset_t的系统调用接口
#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

void printsigset(const sigset_t *set) //打印信号集
{
    int i = 1;
    for(; i < 32; ++i)
    {
        if(sigismember(set, i)) //判断该信号是否在当前信号集中
            cout << "1";
        else
            cout << "0";
    }
    cout << endl;
}

int main()
{
    sigset_t s, p;
    sigemptyset(&s); //初始化信号集，置空
    sigaddset(&s, SIGINT); //Ctrl+C-->SIGINT
    sigprocmask(SIG_BLOCK, &s, NULL); //添加SIGINT信号到阻塞信号集（信号屏蔽字）
    while(1)
    {
        sigpending(&p); //获取未决信号集
        printsigset(&p);
        sleep(1);
    }
    return 0;
}