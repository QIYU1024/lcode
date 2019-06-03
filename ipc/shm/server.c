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
	key_t key = ftok(PATHNAME, PROJ_ID);
	if(key < 0)
	{
		perror("ftok");
		return 1;
	}
	int shmid;
	if((shmid = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | 0666)) < 0) //获取共享内存（物理内存）
	{
		perror("shmget");
		return 2;
	}
	char *addr = (char *)shmat(shmid, NULL, 0); //建立进程地址空间与共享内存的映射
	sleep(3);
	int i = 30;
	while(i--)
	{
		printf("%s\n", addr);
		sleep(1);
	}
	shmdt(addr); //共享内存段与当前进程脱离
	if(shmctl(shmid, IPC_RMID, NULL)) //销毁共享内存
	{
		perror("shmctl");
		return 3;
	}
	return 0;
}
