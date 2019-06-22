#include <iostream>
#include <signal.h>
using namespace std;

void handler(int sig)
{
    cout << "catch a sig : " << sig << endl;
}

int main()
{
    signal(2, handler);
    while(1);
    return 0;
}