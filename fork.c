#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "preshell.h"

extern char **environ;

int proceso_hijo(char **tokens)
{
	pid_t pid;
	int estado;

	pid = fork();

	if (pid == -1)
	{
		perror("fallo fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (tokens != NULL && tokens[0] != NULL)
		{
			ejecucion(tokens);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &estado, 0);
		return (0);
	}
}
