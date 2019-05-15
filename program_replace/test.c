#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("env:	%s	%s\n", getenv("PATH"), getenv("Author"));
	exit(0);
}
