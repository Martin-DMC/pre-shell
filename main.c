#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preshell.h"

int main()
{
	while (1)
	{
		char *comando = NULL;
		size_t largo = 0;
		ssize_t resultado;
		char **tokens = NULL;
		int i = 0, j;

		printf("$ ");

		resultado = getline(&comando, &largo, stdin);
		if (resultado == -1)
			break;
		if (comando[resultado - 1] == '\n') 
			comando[resultado - 1] = '\0';
		if (strcmp(comando, "exit") == 0)
			break;

		tokens = tokenised(comando);
		printf("tokenizado:\n");
		for (j = 0; tokens[j] != NULL; j++)
			printf("%s\n", tokens[j]);

		free(comando);
	}
	return (0);
}
