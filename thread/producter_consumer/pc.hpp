#ifndef __PC_HPP_
#define __PC_HPP_

#include <iostream>
#include <pthread.h>
#include <queue>
using namespace std;

#define NUM 8

class BlockQueue
{
private:
    queue<int> q;
    size_t cap; //队列容量
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;

private:
    void LockQueue()
    {
        pthread_mutex_lock(&mutex);
    }
    void UnLockQueue()
    {
        pthread_mutex_unlock(&mutex);
    }
    void ProducterWait()
    {
        pthread_cond_wait(&full, &mutex); //队列满时阻塞
    }
    void NoticeProducter()
    {
        pthread_cond_signal(&full); //唤醒被条件变量full阻塞的线程
    }
    void ConsumerWait()
    {
        pthread_cond_wait(&empty, &mutex); //队列空时阻塞
    }
    void NoticeConsumer()
    {
        pthread_cond_signal(&empty); //唤醒被条件变量empty阻塞的线程
    }
    bool IsFull()
    {
        return q.size() == cap;
    }
    bool IsEmpty()
    {
        return q.size() == 0;
    }

public:
    BlockQueue(size_t _cap = NUM)
        :cap(_cap)
    {
        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&full, NULL);
        pthread_cond_init(&empty, NULL);
    }

    ~BlockQueue()
    {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&full);
        pthread_cond_destroy(&empty);
    }

    void PushData(const int& val)
    {
        LockQueue();
        while(IsFull())
        {
            NoticeConsumer(); //满，通知消费者消费
            cout << "Queue is full, producter block, consume data." << endl;
            ProducterWait(); //生产者被阻塞
        }
        q.push(val);
        // NoticeConsumer(); //生产一个通知消费者消费
        UnLockQueue();
    }

    void PopData(int& val)
    {
        LockQueue();
        while(IsEmpty())
        {
            NoticeProducter(); //空，通知生产者生产
            cout << "Queue is empty, consumer block, product data." << endl;
            ConsumerWait();
        }
        val = q.front();
        q.pop();
        NoticeProducter(); //消费一个通知生产者生产
        UnLockQueue();
    }
};

#endif