#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid_padre = getppid();
	printf("PID del proceso padre: %d\n", pid_padre);
	return (0);
}
