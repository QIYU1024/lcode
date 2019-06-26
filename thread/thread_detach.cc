#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *run_func(void *arg)
{
    pthread_detach(pthread_self()); //线程自己分离自己
    cout << (char *)arg << endl;
    return (void *)0;
}

int main()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, run_func, (void *)"New thread.") != 0)
    {        
        cout << "pthread_create error" << endl;
        return 1;
    }
    sleep(1); //确认进程先分离
    if(pthread_join(tid, NULL) == 0)
        cout << "thread wait success\n";
    else
        cout << "thread wait failed\n";
    return 0;
}