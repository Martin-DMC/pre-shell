#include <string.h>
#include <stdlib.h>
#include "preshell.h"

extern char **environ;
int conteo(char *cadena)
{
	int nro_token = 0;
	char *token, *copia = strdup(cadena);

	if (copia == NULL)
	{
		perror("fallo dup");
		free(cadena);
		return (1);
	}
	token = strtok(copia, ":");
	while (token != NULL)
	{
		nro_token++;
		token = strtok(NULL, ":");
	}
	free(copia);
	return (nro_token);
}
char **tokens(char *cadena)
{
	char *copia = NULL, *token;
	char **tokens = NULL;
	int j, i = 0, num_t = conteo(cadena);

	tokens = malloc(sizeof(char *) * (num_t + 1));

	if (tokens == NULL)
	{
		perror("malloc fallo");
		free(cadena);
		return (NULL);
	}
	copia = strdup(cadena);
	if (copia == NULL)
	{
		perror("fallo dup");
		free(cadena);
		free(tokens);
		return (NULL);
	}
	token = strtok(copia, ":");
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			perror("fallo dup");
			for (j = 0; j < i; j++)
				free(tokens[j]);
			free(tokens);
			free(copia);
			free(cadena);
			return (NULL);
		}
		token = strtok(NULL, ":");
		i++;
	}
	tokens[i] = NULL;
	free(token);
	free(copia);
	return (tokens);
}
char **_getenv(void)
{
	char **directorios = NULL;
	char *tmp = NULL, *copia = NULL;
	int i = 0, inicio = 0;

	while (*environ != NULL)
	{
		if (strncmp(*environ, "PATH=", 5) == 0)
		{
			tmp = *environ;
			break;
		}
		environ++;
	}
	if (tmp == NULL)
		return (NULL);
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '=')
		{
			i++;
			inicio = i;
		}
		i++;
	}
	i = i - inicio;
	copia = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (tmp[inicio] != '\0')
	{
		copia[i] = tmp[inicio];
		i++;
		inicio++;
	}
	copia[i] = '\0';
	directorios = tokens(copia);
	free(copia);
	return (directorios);
}
