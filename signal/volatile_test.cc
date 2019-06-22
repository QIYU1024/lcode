#include <iostream>
#include <signal.h>
using namespace std;

// int flag = 1;
volatile int flag = 1;

void handler(int signo) //被系统调用所调用
{
    cout << "change flag 1 to 0" << endl;
    flag = 0;
}

int main()
{
    signal(SIGINT, handler);
    while(flag);
    cout << "process quit normal" << endl;
    return 0;
}
//标准情况下，进程收到2号信号时会将flag由1置0，进程正常退出；
//优化情况下（g++ -o $@ $^ -O2），进程不能正常终止，会导致在while(flag)中flag总为1；
//优化会将while监测的flag放入寄存器中，而在handler中修改flag的值被放入内存中
//volatile作用：保持内存可见性，不允许被优化，对该变量进行的任何行为都必须在真实的内存中进行。
/*1> 编译器的优化

在本次线程内, 当读取一个变量时，为提高存取速度，编译器优化时有时会先把变量读取到一个寄存器中；
以后，再取变量值时，就直接从寄存器中取值；当变量值在本线程里改变时，会同时把变量的新值copy到该寄存器中，
以便保持一致。

当变量在因别的线程等而改变了值，该寄存器的值不会相应改变，从而造成应用程序读取的值和实际的变量值不一致。

当该寄存器在因别的线程等而改变了值，原变量的值不会改变，从而造成应用程序读取的值和实际的变量值不一致 
volatile——直接存取原始内存地址*/