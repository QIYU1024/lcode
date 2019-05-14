#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		//sleep(3);
		//int *ptr = NULL; //模拟异常退出
		//*ptr = 1;
		int x = 1/0;
		exit(15);
	}
	else
	{
		int status = 0;
		pid_t result = 0;
		//result = waitpid(-1, &status, 0); //options == 0, 阻塞式等待
		do{
			result = waitpid(-1, &status, WNOHANG); //options == WNOHANG, 非阻塞式等待，利用循环进行轮询	
		}while(result == 0); //有子进程退出，循环退出
		if(WIFEXITED(status) /*&& result == pid*/) 
		//子进程正常退出，pid == -1, 等待任一个子进程，当前只有一个子进程，
		//若有多个子进程时等待特定进程需要判断result == pid,确定子进程，或使用waitpid(pid, &status, 0/WNOHANG)，pid为被等待进程pid
			printf("exit status:	%d\n", WEXITSTATUS(status)); //获取子进程退出码
		else if(WIFSIGNALED(status)) //子进程被信号杀死
			printf("the signal that caused the child process to terminate:	%d\n", WTERMSIG(status)); //获取该信号
	}
}
