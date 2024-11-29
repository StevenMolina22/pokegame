#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io_utils.h"

bool read_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool read_string(const char *str, void *ctx)
{
	char *nuevo = (char *)malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

bool read_char(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}
