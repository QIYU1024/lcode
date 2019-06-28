#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_cond_t cond;
pthread_mutex_t mutex;

void *func1(void *arg)
{
    while(1)
    {
        pthread_cond_wait(&cond, &mutex); //被信号阻塞前，释放已经拥有的锁
        //成功返回后，mutex应由调用线程拥有且已锁定
        cout << "running!" << endl;
    }
}

void *func2(void *arg)
{
    while(1)
    {
        pthread_cond_signal(&cond);
        sleep(1);
    }
}

int main()
{
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
    
    pthread_t tid1, tid2;
    
    if(pthread_create(&tid1, NULL, func1, NULL) != 0)
    {
        cout << "pthread_create error!" << endl;
        return 1;
    }
    if(pthread_create(&tid2, NULL, func2, NULL) != 0)
    {
        cout << "pthread_create error!" << endl;
        return 1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}