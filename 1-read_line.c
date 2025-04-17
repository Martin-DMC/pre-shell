#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *comando = NULL;
	size_t largo = 0;
	ssize_t resultado;

	printf("$ ");
	resultado = getline(&comando, &largo, stdin);

	if (resultado != -1)
	{
		printf("%s", comando);
	}
	free(comando);
	return (0);
}
