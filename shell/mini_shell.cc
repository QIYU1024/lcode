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

void redirect(string& cmd)
{
	//处理 >, >>
	int index;
	if((index = cmd.find('>')) != string::npos)
	{
		int flag = index;
		string symbol;
		symbol += '>';
		if(cmd[index+1] == '>')
			symbol += '>';
		while(cmd[index] == ' ' || cmd[index] == '>') { ++index; } //跳过
		string str(cmd, 0, flag); //> 之前
		string temp(cmd, index); //重定向到
		cmd = str;
		char file[MAXNO] = {0};
		strcpy(file, temp.c_str());
		int fd;
		if(symbol == ">")
			fd = open(file, O_WRONLY|O_CREAT, 00644);
		else if(symbol == ">>")
			fd = open(file, O_CREAT|O_WRONLY|O_APPEND, 00644);
		dup2(fd, 1);
	}
}

int main()
{
	string prompt = "[qiyu@mini_shell xxx]# ";
	while(1)
	{
		cout << prompt;
		char command[MAXNUM] = {0};
		fgets(command, MAXNUM, stdin);
		command[strlen(command)-1] = 0; //delete '\n'
		string cmd = command;
		pid_t pid = fork();
		if(pid == 0)
		{
			redirect(cmd);
			if(strlen(command) != cmd.size())
				strcpy(command, cmd.c_str());
			char *argv[MAXNO];
			strtoargv(command, argv);
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
