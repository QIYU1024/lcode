#include <stdio.h>
#include <ctype.h>

int main()
{
	char c;
	printf("pid: %d\n", getpid());
	while((c = getchar()) != EOF)
	{
		if(islower(c))
			c -= ('a'-'A');
		if(putchar(c) == EOF)
			perror("putchar error\n");
		if(c == '\n')
			fflush(stdout);
	}
	return 0;
}
