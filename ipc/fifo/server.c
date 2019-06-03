#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
do{ \
	perror(m);\
	exit(EXIT_FAILURE); \
}while(0)

int main()
{
	if(mkfifo("myfifo", 0644) < 0)
		ERR_EXIT("mkfifo");
	int fd = open("myfifo", O_RDONLY);
	if(fd < 0)
		ERR_EXIT("open");
	char buff[1024] = {0};
	while(1)
	{
		printf("Please Wait...\n ");
		ssize_t s = read(fd, buff, sizeof(buff)-1);
		if(s > 0)
		{
			buff[s] = 0;
			printf("Client say: %s\n", buff);
		}
		else if(s == 0)
			printf("Client quit!\n");
		else
			ERR_EXIT("read");
	}
	close(fd);
	return 0;
}
