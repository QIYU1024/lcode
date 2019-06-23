#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

pthread_t tid;

void printids(const char *s)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    cout << s << "pid: " << pid << " tid: " << tid << endl;
}

void *thr_fn(void *arg)
{
    printids((char *)arg);
    return (void *)0;
}

int main()
{
    int err;
    err = pthread_create(&tid, NULL, thr_fn, (void *)"New thread: ");
    if(err != 0)
        cout << "pthread_create error" << endl;
    pthread_join(tid, NULL);
    printids("Main thread: ");
    return 0;
}