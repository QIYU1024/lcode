#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	int infd = open("tp", O_RDONLY);
	if(infd == -1)
	{
		printf("open");
		exit(0);
	}
	int outfd = open("file.bak", O_WRONLY);
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
	return 0;
}
