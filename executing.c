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
	char *copia = NULL, *directorio = NULL, *ruta_final = NULL;
	char *path_env = getenv("PATH");

	if (path_env == NULL)
		return (NULL);

	copia = strdup(path_env);
	if (copia == NULL)
	{
		perror("fallo dup\n");
		return (NULL);
	}
	directorio = strtok(copia, ":");
	while (directorio != NULL)
	{
		if (asprintf(&ruta_final, "%s/%s", directorio, comando) == -1)
		{
			perror("fallo asprintf\n");
			free(copia);
			return (NULL);
		}
		if (access(ruta_final, X_OK) == 0)
		{
			free(copia);
			return (ruta_final);
		}
		free(ruta_final);
		ruta_final = NULL;
		directorio = strtok(NULL, ":");
	}
	free(copia);
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
		fprintf(stderr, "%s: command not found\n", tokens[0]);
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
