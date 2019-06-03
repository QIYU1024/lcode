#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define PATHNAME "/usr/bin/"
#define PROJ_ID 0x6666
#define SIZE 4096
int main()
{
	key_t key = ftok(PATHNAME, PROJ_ID); //生成key
	if(key < 0)
	{
		perror("ftok");
		return 1;
	}
	int shmid;
	if((shmid = shmget(key, SIZE, IPC_CREAT)) < 0)
	{
		perror("shmget");
		return 2;
	}
	printf("%d\n", shmid);
	char *addr = (char *)shmat(shmid, NULL, 0);
	printf("%p\n", addr);
	int i = 0;
	char c = 'a';
	while(1) //向共享内存写数据
	{
		addr[i++] = (c++);
		addr[i] = 0; //'\0'
		sleep(1);
	}
	shmdt(addr);
	return 0;
}
