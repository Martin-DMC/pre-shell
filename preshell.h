#include <stddef.h>
#include <stdio.h>
#ifndef PRESHELL_H
#define PRESHELL_H

ssize_t _getline(char **ptrline, size_t *size, FILE *stream);
char **tokenised(char *comando);
int ejecucion(char **tokens);
int proceso_hijo(char **tokens);


#endif
