#ifndef IO_SPLIT_H
#define IO_SPLIT_H
#include <stdio.h>

typedef struct {
	size_t len;
	char **arr;
} Vec;

/**
 * Divide una cadena en partes utilizando un separador especificado.
 *
 * str La cadena a dividir.
 * sep El carácter separador.
 * devuelve un puntero a una estructura Vec que contiene las partes divididas,
 *         o NULL si ocurre un error durante la división.
 */
Vec *dividir_string(const char *str, char sep);

/**
 * Libera la memoria ocupada por las partes de una estructura Vec.
 *
 * partes Puntero a la estructura Vec que contiene las partes a liberar.
 */
void liberar_partes(Vec *partes);

#endif
