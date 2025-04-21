#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "preshell.h"

extern char **environ;

char *verificar_ruta(char *comando)
{
	if ((strchr(comando, '/') != NULL) && (access(comando, X_OK) == 0))
		return (strdup(comando));
	return (NULL);
}
char *generar_ruta(char *comando)
{
	char *ruta_final = NULL;
	char **path_dir = _getenv();
	int i, j;


	if (path_dir == NULL)
	{
		perror("fallo _getenv");
		return (NULL);
	}
	for (i = 0; path_dir[i] != NULL; i++)
	{
		if (asprintf(&ruta_final, "%s/%s", path_dir[i], comando) == -1)
		{
			perror("fallo asprintf\n");
			for (j = 0; path_dir[j] != NULL; j++)
				free(path_dir[i]);
			free(path_dir);
			return (NULL);
		}
		if (access(ruta_final, X_OK) == 0)
		{
			for (j = 0; path_dir != NULL; j++)
				free(path_dir[i]);
			free(path_dir);
			return (ruta_final);
		}
		free(ruta_final);
		ruta_final = NULL;
	}
	for (j = 0; path_dir[j] != NULL; j++)
		free(path_dir[j]);
	free(path_dir);
	return (NULL);
}
char *buscar_comando(char *comando)
{
	char *ruta = verificar_ruta(comando);
	if (ruta)
		return (ruta);
	return (generar_ruta(comando));
}
int ejecucion(char **tokens)
{
	char *ruta_comando = buscar_comando(tokens[0]);

	if (ruta_comando == NULL)
	{
		fprintf(stderr, "preshell: 1: %s: not found\n", tokens[0]);
		return (-1);
	}
	if (execve(ruta_comando, tokens, environ) == -1)
	{
		perror("fallo ejecucion\n");
		free(ruta_comando);
		return (-1);
	}
	free(ruta_comando);
	return (0);
}
