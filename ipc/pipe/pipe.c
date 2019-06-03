#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>


#define ERR_EXIT(m)\
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)       //写宏时用do while()包起来，很棒的写法

int main()
{
	int pipefd[2];
	if(pipe(pipefd) == -1)
		ERR_EXIT("pipe error");
	pid_t pid = fork();
	if(pid == -1)
		ERR_EXIT("fork error");
	
	//if(pid == 0)
	//{
	//	close(pipefd[0]);
	//	int i = 3;
	//	while(i--)
	//	{
	//		write(pipefd[1], "hello", 5);
	//		sleep(1);
	//	}
	//	close(pipefd[1]);
	//	exit(EXIT_SUCCESS);
	//}
	//else
	//{
	//	close(pipefd[1]);
	//	char buf[10] = {0};
	//	while(1)
	//	{
	//		ssize_t val = read(pipefd[0], buf, 10); //当所有管道写端对应的文件描述符被关闭，read返回0
	//		printf("%s	%u\n", buf, val);
	//		sleep(1);
	//	}
	//}
	
	if(pid == 0)
	{
		close(pipefd[0]);
		int i = 3;
		while(i--)
		{
			write(pipefd[1], "hello", 5);
		}
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		close(pipefd[0]); //关闭管道读端
		int status;
		wait(&status);
		printf("%d\n", status & 0x7F); //低7位，终止信号
		//当管道读端被关闭，write进程会被SIGPIPE杀死
	}
	return 0;
}
