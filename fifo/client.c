#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define ERR_EXIT(m) \
do{ \
	perror(m);\
	exit(EXIT_FAILURE); \
}while(0)

int main()
{
	int fd = open("myfifo", O_WRONLY);
	if(fd < 0)
		ERR_EXIT("open");
	char buff[1024] = {0};
	while(1)
	{
		printf("Please Enter: ");
		fflush(stdout);
		ssize_t s = read(0, buff, sizeof(buff)-1);
		if(s > 0)
		{
			buff[s-1] = 0; //delete '\n'
			write(fd, buff, strlen(buff));
		}
		else
			ERR_EXIT("read");
	}
	close(fd);
	return 0;
}
