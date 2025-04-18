#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

ssize_t _getline(char **ptrline, size_t *size, FILE *stream)
{
	char buffer[520];
	ssize_t buf_pos = 0, buf_tam = 0, l_leidas;
	size_t tam_line = 0, new_size;
	char *line = *ptrline, *new_line;

	if (!ptrline || !size || !stream)
		return (-1);
	if (*ptrline == NULL)
	{
		*ptrline = malloc(220);
		if (*ptrline == NULL)
			return (-1);
		*size = 220;
	}
	line = *ptrline;
	while (1)
	{
		if (buf_pos >= buf_tam)
		{
			buf_tam = read(fileno(stream), buffer, sizeof(buffer));
			buf_pos = 0;
			if (buf_tam == 0)
			{
				if (tam_line > 0)
				{
					line[tam_line] = '\0';
					return (tam_line);
				}
				return (0);
			}
			if (buf_tam == -1)
			{
				return (-1);
			}
		}
		while (buf_pos < buf_tam)
		{
			line[tam_line++] = buffer[buf_pos];
			if (buffer[buf_pos++] == '\n')
			{
				line[tam_line] = '\0';
				*ptrline = line;
				*size = tam_line;
				return (tam_line);
			}
			if (tam_line >= *size - 1)
			{
				new_size = *size * 2;
				new_line = realloc(line, new_size);
				if (!new_line)
				{
					free(line);
					return (-1);
				}
				line = new_line;
				*ptrline = line;
				*size = new_size;
			}
		}
	}
	return (-1);
}
