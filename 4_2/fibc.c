#include <stdio.h>

int fibc(int i)
{
  if((i == 1) || (i == 2))
    return 1;
  else{
    return fibc(i-1)+fibc(i-2);
  }
}

int main()
{
  int i = 20;
  printf("FibNO.%d: %d\n", i, fibc(i));
  return 0;
}
