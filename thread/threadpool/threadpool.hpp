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
        ThreadPool *tp = (ThreadPool *)arg; //不能用this指针，使用参数传入一个对象指针，用来访问成员方法
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

class Singleton //单例
{
private:
    static ThreadPool *tp;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
public:
    ThreadPool *GetInstance()
    {
        if(tp == NULL)
        {
            pthread_mutex_lock(&mutex); //为null时再加锁，避免当已经存在对象是仍需要等待获得锁
            if(tp == NULL) //再次判断可避免在第一次判断和获得锁之间，有其他线程先一步为单例获得对象
            {
                tp = new ThreadPool(5);
                tp->InitThreadPool();
            }
            pthread_mutex_unlock(&mutex);
        }
        return tp;
    }
};

ThreadPool *Singleton::tp = NULL;

#endif