#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("start mysqld.service...\n");
		execlp("systemctl", "systemctl", "start", "mysqld", NULL);	
	}
	else
	{
		//wait(NULL);
		waitpid(pid, NULL, 0);
		printf("root log in mysql...\n");
		execlp("mysql", "mysql", "-u", "root", "-p", NULL);
	}
	exit(0);
}
