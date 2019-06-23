//线程终止的三种方式
#include <iostream>
#include <pthread.h>
using namespace std;

void *thr_fn(void *arg)
{
    cout << "New thread, ";
    // return (void *)11; //（1）线程return返回
    // pthread_exit((void *)11); //（2）调用pthread_exit()结束线程
}

int main()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, thr_fn, NULL) != 0)
        cout << "ptheard_create error!" << endl;
    pthread_cancel(tid); //（3）新线程被主线程取消
    void *ret_val;
    pthread_join(tid, &ret_val);
    cout << "exit code: " << (long)ret_val << endl;
    return 0;
}