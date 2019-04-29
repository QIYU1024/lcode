#include <stdio.h>
#include <unistd.h>

int main()
{
	int i = 0;
	for(; i < 3; ++i)
	{
		fork();
	}
	sleep(30);
	return 0;
}
