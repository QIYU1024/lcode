#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

#define MAXNUM 1024
#define MAXNO 32

void strtoargv(char *str, char **argv)
{
	argv[0] = strtok(str, " ");
	int i = 0;
	while (argv[i] != NULL)
	{
		++i;
		argv[i] = strtok(NULL, " ");
	}
}
int main()
{
	string prompt = "[qiyu@mini_shell xxx]# ";
	while(1)
	{
		cout << prompt;
		char command[MAXNUM];
		fgets(command, MAXNUM, stdin);
		command[strlen(command)-1] = 0; //delete '\n'
		char *argv[MAXNO];
		strtoargv(command, argv);
		int i = 0;
		char *file = NULL;
		for (; argv[i] != NULL; ++i)
		{
			if(0 == strcmp(">", argv[i]))
			{
				argv[i] = NULL;
				if(argv[i+1] != NULL)
					file = argv[i+1];
			}
		}
		pid_t pid = fork();
		if(pid == 0)
		{
			if(file != NULL)
			{
				open(file, O_WRONLY|O_CREAT, 00644);
				dup2(3, 1);
			}
			execvp(argv[0], argv);
		}
		else
		{
			int status;
			waitpid(pid, &status, 0);
		}
	}
	//argv[i-1] = NULL;
	//for (i = 0; argv[i] != NULL; ++i)
	//{
	//	cout << i << ":" << argv[i] << endl;
	//}
	return 0;
}
