#include "pc.hpp"
#include <ctime>
#include <unistd.h>
#include <cstdlib>

void *Producter(void *arg)
{
    CircleQueue *cq = (CircleQueue *)arg;
    while(1)
    {
        int data = rand() % 100 + 1;
        cq->PushData(data);
        cout << "Product data: " << data << endl;
        sleep(1); //1秒生产一个
    }
    return (void *)0;
}

void *Consumer(void *arg)
{
    CircleQueue *cq = (CircleQueue *)arg;
    int data;
    while(1)
    {
        cq->PopData(data);
        cout << "Consume data: " << data << endl;
        // sleep(1); //1秒消费一个
    }
    return (void *)0;
}

int main()
{
    srand((unsigned int)time(NULL));
    pthread_t c, p;
    CircleQueue cq;
    pthread_create(&p, NULL, Producter, (void *)&cq);
    pthread_create(&c, NULL, Consumer, (void *)&cq);

    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return 0;
}