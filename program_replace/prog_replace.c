#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//int main()
//{
//	//execl("./main", "main", "arg1", "arg2", NULL);
//	execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
//	exit(0);
//}
//
//int main()
//{
//	//在path中自动查找ls
//	execlp("ls", "ls", "-a", "-l", NULL); //新程序参数列表中第一个参数为其本身"ls"
//	exit(0);
//}
//
//int main()
//{
//	//v:参数在数组中，以NULL结尾
//	char *const argv[] = {"top", NULL};
//	execvp("top", argv);
//	exit(0);
//}

int main()
{
	char *const argv[] = {"test", NULL};
	char *const envp[] = {"PATH=/usr/bin/", "Author=QIYU", NULL}; //为新程序维护的环境变量

	execve("./test", argv, envp);
	exit(0);
}
