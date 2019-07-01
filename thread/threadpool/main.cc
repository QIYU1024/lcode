#include "threadpool.hpp"
#include <cstdlib>
#include <ctime>

int Add(int x, int y)
{
    return x + y;
}
int Sub(int x, int y)
{
    return x - y;
}
int Mul(int x, int y)
{
    return x * y;
}
int Div(int x, int y)
{
    return x / y;
}

int main()
{
    srand((unsigned int)time(NULL));
    hander func_arr[] = {Add, Sub, Mul, Div}; //模拟线程执行的任务
    ThreadPool *tp = Singleton().GetInstance();
    while(1)
    {
        int x = rand() % 20 + 1;
        int y = rand() % 5 + 1;
        int index = rand() % 4;
        Task t = Task(x, y, func_arr[index]);
        cout << "Put task: " << x << " "<< index << " " << y << endl;
        tp->PutTask(t);
        sleep(1);
    }
    return 0;
}