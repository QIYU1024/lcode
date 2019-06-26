#include <iostream>
#include <pthread.h>
#include <unistd.h>
// #include <sys/types.h>
#include <sys/syscall.h>
using namespace std;

void *run_func(void *arg)
{
    while(1)
    {
        cout << (char *)arg << " ";
        // cout << "thread_id: " << gettid() << ", "; //不可用
        cout << "thread_id: " << syscall(SYS_gettid) << ", "; //LWP(轻量级进程)值，是操作系统层面的线程id，OS调度时使用
        // cout << "process_id: " << getpid() << endl; //进程id，线程组id
        cout << "pthread_thread_id: " << pthread_self() << endl; //用户级线程库pthread的线程id
        //在NPTL实现中，线程id(pthread_self()返回值)本质上是该线程(struct_pthread)在进程地址空间中的起始地址
        sleep(1);
    }
    return (void *)0;
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, run_func, (void *)"Thread1 running.");
    pthread_create(&tid2, NULL, run_func, (void *)"Thread2 running.");
    run_func((void *)"Main thread running.");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}