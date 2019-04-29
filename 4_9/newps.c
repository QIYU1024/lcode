#include <stdio.h>
#include <unistd.h>

int value; //init 0, child,parent process diff value, processes independent
int main()
{
	pid_t a = fork();
	if(a < 0)
	{
		printf("error!\n");
	}
	else if(a == 0) //child
	{
		for(;;)
		{
			//printf("child process value = %d\n", value++); //value++
			printf("child process value address = %p\n", &value);
			sleep(1);
		}
	}
	else //parent
	{
		for(;;)
		{
			//printf("parent process value = %d\n", value); //0
			printf("parent process value address = %p\n", &value);
			sleep(1);
		}
	}
	return 0;
}
//&value(在地址空间中的偏移地址)相同，在各自地址空间中变量value的偏移量相同，
//因为child完全拷贝parent（包括虚拟地址空间）,但内存独立
