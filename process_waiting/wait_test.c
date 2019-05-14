#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t ret = fork();
	if(ret == 0) //child
	{
		sleep(2);
		exit(15); //15为该进程退出码
	}
	else //parent
	{
		int status = 0;
		int result = wait(&status);
		if(result > 0)
		{
			printf("waiting success, status = %d\n", status);	
			printf("exit signal: %d\n", status & 0x7F); //低7位为终止信号
			printf("exit status: %d\n", (status >> 8) & 0xFF); //次8位为退出状态（被等待进程退出码）
		}
		else
			printf("waiting failed!\n");
	}
}
