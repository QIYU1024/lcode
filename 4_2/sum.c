#include <stdio.h>

int MySum()
{
  int i = 0;
  int sum = 0;
  for(; i <= 100; ++i)
  {
    sum += i;
  }
  return sum;
}

int main()
{
  int sum = MySum();
  printf("sum = %d\n", sum);
  return 0;
}
