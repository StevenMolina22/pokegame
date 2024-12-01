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

char* my_strdup(const char* str) {
    // Check if the input string is NULL
    if (str == NULL) {
        return NULL;
    }

    // Calculate the length of the string
    size_t length = strlen(str);

    // Allocate memory for the new string (length + 1 to include null terminator)
    char* duplicate = (char*)malloc(length + 1);

    // Check if memory allocation was successful
    if (duplicate == NULL) {
        return NULL;
    }

    // Copy the original string to the newly allocated memory
    strcpy(duplicate, str);

    return duplicate;
}
