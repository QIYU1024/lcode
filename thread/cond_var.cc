#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_cond_t cond;
pthread_mutex_t mutex;

// void *func1(void *arg)
// {
//     while(1)
//     {
//         pthread_cond_wait(&cond, &mutex); //被信号阻塞前，释放已经拥有的锁
//         //成功返回后，mutex应由调用线程拥有且已锁定
//         cout << "running!" << endl;
//     }
// }

// void *func2(void *arg)
// {
//     while(1)
//     {
//         pthread_cond_signal(&cond);
//         sleep(1);
//     }
// }

void *func1(void *arg)
{
    pthread_mutex_lock(&mutex);
    cout << (char *)arg << " coming!" << endl;
    pthread_cond_wait(&cond, &mutex); 
    pthread_mutex_unlock(&mutex);
    return (void *)0;
}

int main()
{
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
    
    pthread_t tid1, tid2, tid3;
    
    if(pthread_create(&tid1, NULL, func1, (void *)"thread1") != 0)
    {
        cout << "pthread_create error!" << endl;
        return 1;
    }
    if(pthread_create(&tid2, NULL, func1, (void *)"thread2") != 0)
    {
        cout << "pthread_create error!" << endl;
        return 1;
    }
    if(pthread_create(&tid3, NULL, func1, (void *)"thread3") != 0)
    {
        cout << "pthread_create error!" << endl;
        return 1;
    }
    
    sleep(5);
    pthread_cond_broadcast(&cond);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}

// void *func(void *arg)
// {
//     pthread_mutex_lock(&mutex);
//     while(cond_is_false)
//     {
//         pthread_cond_wait(&cond, &mutex);
//     }
//     //...
//     pthread_mutex_unlock(&mutex);
//     return (void *)0;
// }

//条件变量使用规范
// pthread_mutex_lock(&mutex);
// while(条件为假)
// {
//     pthread_cond_wait(&cond, &mutex);
// }
// 修改条件
// pthread_mutex_unlock(&mutex);

// pthread_mutex_lock(&mutex);
// 设置条件为真
// pthread_cond_signal(&cond);
// pthread_mutex_unlock(&mutex);
