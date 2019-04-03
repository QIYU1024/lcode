#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 102

int main()
{
  char* bar = (char*)malloc(SIZE * sizeof(char));
  memset(bar, '\0', SIZE*sizeof(char));
  const char* lable = "|/-\\";
  int i = 0;
  for(; i < SIZE-1; ++i)
  {
    printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
    fflush(stdout);
    bar[i] = '#';
    usleep(10000);
  }
  printf("\n");
  return 0;
}
