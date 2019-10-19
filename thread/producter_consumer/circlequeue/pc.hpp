#ifndef __PC_HPP_
#define __PC_HPP_

#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define NUM 6

class CircleQueue
{
private:
    vector<int> rq; //用数组模拟环形队列，对下标取模来模拟环状
    size_t cap;
    sem_t data_sem; //队列中空位数
    sem_t space_sem; //队列中数据个数
    size_t product_step;
    size_t consume_step;

public:
    CircleQueue(size_t _cap = NUM)
        :rq(_cap)
        , cap(_cap)
    {
        sem_init(&data_sem, 0, 0);
        sem_init(&space_sem, 0, cap);
        product_step = consume_step = 0;
    }

    ~CircleQueue()
    {
        sem_destroy(&data_sem);
        sem_destroy(&space_sem);
    }

    void PushData(const int& val)
    {
        sem_wait(&space_sem); //space--,P
        rq[product_step] = val; //存在线程不安全问题，有可能多个线程同时进入区间41~43行。
        ++product_step;
        product_step %= cap;
        sem_post(&data_sem); //data++,V
    }

    void PopData(int& val)
    {
        sem_wait(&data_sem); //data--
        val = rq[consume_step];
        ++consume_step;
        consume_step %= cap;
        sem_post(&space_sem); //space++
    }
};

#endif //__PC_HPP_
