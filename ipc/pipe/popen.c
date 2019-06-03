#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

int main()
{
	FILE *fp = popen("ls -al", "r");
	if(fp == NULL)
		ERR_EXIT("popen");
	int fd = open("file", O_WRONLY | O_CREAT, 0644);
	if(fd == -1)
		ERR_EXIT("open");
	char *buff[1024] = {0};
	fread(buff, 1024, 1, fp);
	do
	{
		write(fd, buff, sizeof(buff));
	}while(fread(buff, 1024, 1, fp) != 0);
	pclose(fp);
	close(fd);
	return 0;
}
//利用popen()执行命令“ls -al”，将结果输入管道，
//popen(, "r")返回仅可读的文件指针，读取管道内容到file中
