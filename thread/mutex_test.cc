#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int tickets = 100; //车票数为共享变量
pthread_mutex_t lock/*  = PTHREAD_MUTEX_INITIALIZER */;

void *buyticket(void *arg)
{
    while(1)
    {   
        pthread_mutex_lock(&lock); //通过互斥量确保对tickets的访问是线程安全的
        if(tickets > 0)
        {
            usleep(1000);
            cout << (char *)arg << "buy ticket: " << tickets <<endl;
            --tickets;
        }
        else
        {
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);
    }
    pthread_exit((void *)0);
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    pthread_t tid4;
    pthread_create(&tid1, NULL, buyticket, (void *)"Thread1,");
    pthread_create(&tid2, NULL, buyticket, (void *)"Thread2,");
    pthread_create(&tid3, NULL, buyticket, (void *)"Thread3,");
    pthread_create(&tid4, NULL, buyticket, (void *)"Thread4,");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}