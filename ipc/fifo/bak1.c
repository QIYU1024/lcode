#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <wait.h>

int main()
{
	mkfifo("tp", 0644);
	int infd = open("file", O_RDONLY);
	if(infd == -1)
	{
		printf("open");
		exit(0);
	}
	int outfd = open("tp", O_WRONLY);
	if(outfd == -1)
	{
		printf("open");
		exit(0);
	}
	char buf[1024];
	int n;
	while((n = read(infd, buf, 1024)) > 0)
	{
		write(outfd, buf, n);
	}
	close(infd);
	close(outfd);
	//内核为至少一个进程打开的每个FIFO特殊文件保留一个管道对象。
	//在传递数据之前，必须在两端打开FIFO（读取和写入）。通常，打开FIFO块直到另一端打开。
	//进程可以在非阻塞模式下打开FIFO。在这种情况下，即使在写入端没有打开任何人，
	//只读打开也会成功，只读打开将因ENXIO（没有这样的设备或地址）而失败，除非另一端已经打开。
	return 0;
}
