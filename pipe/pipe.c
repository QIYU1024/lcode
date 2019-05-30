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
	
	if(pid == 0)
	{
		close(pipefd[0]);
		write(pipefd[1], "hello", 5);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		char buf[10] = {0};
		read(pipefd[0], buf, 10);
		printf("%s\n", buf);
	}
	return 0;
}
