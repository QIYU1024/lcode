#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(m) \
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

int main()
{
	char buff[1024] = {0};
	FILE *fp = NULL;
	printf("main pid: %d\n", getpid());
	if((fp = popen("./my_prog", "r")) == NULL)
		ERR_EXIT("popen");
	while(1)
	{
		printf("prompt> ");
		fflush(stdout);
		if(fgets(buff, 1024, fp) == NULL)
			break;
		if(fputs(buff, stdout) == EOF)
			ERR_EXIT("fputs");
	}
	pclose(fp);
	return 0;
}
//popen()先创建管道，再创建子进程，将子进程的输出改为管道的写端(dup2())，
//子进程再进行程序替换(execve())去执行"./my_prog"，
//（在my_prog中,读取标准输入，将小写转大写，遇到'\n'，刷新缓冲区到管道, 循环重复）
//fgets()读取管道内容到buff，fputs打印buff内容
