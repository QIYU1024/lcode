#include <iostream>
using namespace std;
#include <unistd.h>
#include <stdlib.h>

int main()
{
//  while(true)
//  {
//    cout << "This is a Process." << endl;
//    sleep(1);
//  }
//  cout << "current process PID:" << getpid() << endl;
//  cout << "father process PID:" << getppid() << endl;
  pid_t id = fork();
  if(id < 0)
  {
    cerr << "fork error" << endl;
  }
  else if(id == 0)
  {
    cout << "I am child, PID:" << getpid() << endl;
    sleep(30);
  }
  else
  {
    cout << "I am parent, PID:" << getpid() << endl;
    sleep(5);
    exit(1);
  }
  return 0;
}
