#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

bool read_int(const char *str, void *ctx);
bool read_string(const char *str, void *ctx);
bool read_char(const char *str, void *ctx);
char* str_copy(const char* str);

#endif // UTILS_H
