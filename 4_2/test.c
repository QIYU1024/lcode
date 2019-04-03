#include <stdio.h>
#include <unistd.h>

//int main()
//{
//  printf("hello Linux!");
//  sleep(3);
//  return 0;
//}
//printf遇到'\n'刷新缓冲区或程序结束刷新

int main()
{
  printf("hello Linux!");
  fflush(stdout);
  //显示刷新缓冲区
  sleep(3);
  return 0;
}
