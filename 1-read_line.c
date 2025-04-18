#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preshell.h"

int main()
{
	char *comando = NULL, *token, *cop_div = NULL, *copia = NULL;
	size_t largo = 0;
	ssize_t resultado;
	char **tokens = NULL;
	int cant_token = 0, i = 0, j;

	printf("$ ");

	resultado = getline(&comando, &largo, stdin);
	if (resultado != -1)
	{
		printf("%s\n", comando);

		copia = strdup(comando);
		if (copia == NULL)
		{
			perror("fallo duplicado");
			free(comando);
			return (1);
		}
		token = strtok(copia, " ");
		while (token != NULL)
		{
			cant_token++;
			token = strtok(NULL, " ");
		}
		tokens = malloc(sizeof(char *) * (cant_token + 1));
		if (tokens == NULL)
		{
			perror("malloc a fallado");
			free(comando);
			return (-1);
		}
		cop_div = strdup(comando);
		if (cop_div == NULL)
		{
			perror("fallo duplicado");
			free(comando);
			free(tokens);
			return (-1);
		}
		token = strtok(cop_div, " ");
		while (token != NULL)
		{
			tokens[i] = strdup(token);
			if (tokens[i] == NULL)
			{
				perror("fallo duplicado");
				for (j = 0; j < i; j++)
				{
					free(tokens[j]);
				}
				free(tokens);
				free(copia);
				free(comando);
				return (-1);
			}
			token = strtok(NULL, " ");
			i++;
		}
		tokens[i] = NULL;
		printf("tokens: \n");
		for (j = 0; tokens[j] != NULL; j++)
		{
			printf("%s\n", tokens[j]);
			free(tokens[j]);
		}
		free(tokens);
		free(copia);

	}
	free(comando);
	return (0);
}
