#include <stdio.h>

int main(int ac, char **av)
{
	int i;
	char *texto;

	for (i = 1; ; i++)
	{
		texto = av[i];
		if (texto == NULL)
			break;
		if (i != 1)
		{
			printf(" %s", texto);
		}
		else
		{
			printf("%s", texto);
		}
	}
	printf("\n");
}
