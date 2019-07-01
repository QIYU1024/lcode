#ifndef __THREADPOOL_H_
#define __THREADPOOL_H_

#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
using namespace std;

typedef int (*hander) (int, int);

class Task
{
public:
    int _x;
    int _y;
    hander _func;
public:
    Task(const int& x, const int& y, hander func)
        :_x(x)
        ,_y(y)
        ,_func(func)
    {}
    void Run()
    {
        cout << pthread_self() << " result: " << _func(_x, _y) << endl;
    }
};

class ThreadPool
{
private:
    queue<Task> task_queue;
    size_t thread_count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
private:
    void LockQueue()
    {
        pthread_mutex_lock(&mutex);
    }
    void UnLockQueue()
    {
        pthread_mutex_unlock(&mutex);
    }
    void BlockThread()
    {
        pthread_cond_wait(&cond, &mutex);
    }
    void SignalThread()
    {
        pthread_cond_signal(&cond);
    }
    Task GetTask()
    {
        Task t = task_queue.front();
        task_queue.pop();
        return t;
    }

public:
    ThreadPool(size_t count = 3)
        :thread_count(count)
    {}
    static void *run_func(void *arg) //static函数没有参数this
    {
        ThreadPool *tp = (ThreadPool *)arg;
        while(1)
        {
            tp->LockQueue();
            while(tp->task_queue.empty())
            {
                tp->BlockThread(); //当前没有任务，线程被阻塞
            }
            //poptaskqueue
            Task t = tp->GetTask();
            //unlockmutex
            tp->UnLockQueue();
            //runtask
            t.Run(); //在锁外执行任务
        }
    }
    void InitThreadPool()
    {
        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&cond, NULL);
        pthread_t tid;
        while(thread_count--)
        {
            pthread_create(&tid, NULL, run_func, (void *)this);
        }
    }
    void PutTask(const Task& t)
    {
        LockQueue();
        task_queue.push(t);
        UnLockQueue();
        SignalThread();
    }
    ~ThreadPool()
    {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
    }
};

class Singleton
{
private:
    static ThreadPool *tp;
public:
    ThreadPool *GetInstance()
    {
        if(tp == NULL)
        {
            tp = new ThreadPool(5);
            tp->InitThreadPool();
        }
        return tp;
    }
};

ThreadPool *Singleton::tp = NULL;

#endif