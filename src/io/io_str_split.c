#include "io_str_split.h"
#include <stdlib.h>
#include <string.h>

// Funciones auxiliares
size_t contar_separadores(const char *str, char sep)
{
	if (str == NULL)
		return 0;
	size_t contador = 1;

	const char *temp = str;
	while (*temp) {
		if (*temp == sep)
			contador++;
		temp++;
	}

	return contador;
}

Vec *vec_nuevas_partes(size_t len)
{
	Vec *partes = (Vec *)malloc(sizeof(Vec));
	partes->arr = (char **)malloc(len * sizeof(char *));
	partes->len = len;

	return partes;
}

Vec *dividir_string(const char *string, char separador)
{
	if (string == NULL)
		return vec_nuevas_partes(0);

	size_t countador_sep = contar_separadores(string, separador);
	size_t len = strlen(string);
	Vec *partes = vec_nuevas_partes(countador_sep);

	size_t inicio = 0;
	size_t sub_idx = 0;

	// Anade substrings
	for (size_t final = 0; final <= len; final++) {
		if (string[final] != separador && string[final] != '\0')
			continue;

		size_t sub_len = final - inicio;
		partes->arr[sub_idx] =
			(char *)malloc((sub_len + 1) * sizeof(char));

		strncpy(partes->arr[sub_idx], &string[inicio], sub_len);
		partes->arr[sub_idx][sub_len] = '\0';

		sub_idx++;
		inicio = final + 1;
	}

	return partes;
}

void liberar_partes(Vec *partes)
{
	if (partes == NULL)
		return;

	for (size_t i = 0; i < partes->len; i++) {
		free(partes->arr[i]);
	}
	free(partes->arr);
	free(partes);
}
