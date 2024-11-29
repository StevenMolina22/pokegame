#include "io_csv.h"
#include <stdio.h>
#include <string.h>
#include "io_str_split.h"

#define MAX_LINEAS 1024

struct archivo_csv {
	char sep;
	FILE *file;
};

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo,
				      char separador)
{
	FILE *file = fopen(nombre_archivo, "r");
	if (!file)
		return NULL;

	struct archivo_csv *csv =
		(struct archivo_csv *)malloc(sizeof(struct archivo_csv));
	if (!csv)
		return NULL;

	csv->file = file;
	csv->sep = separador;
	return csv;
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	if (archivo == NULL || archivo->file == NULL) {
		return 0;
	}

	char buffer[MAX_LINEAS];
	char *result = fgets(buffer, sizeof(buffer), archivo->file);
	if (!result)
		return 0;

	Vec *cols = dividir_string(buffer, archivo->sep);

	size_t i = 0;
	while (cols->len <= columnas && i < columnas) {
		if (funciones[i] == NULL) {
			// if func is null should not continue
			liberar_partes(cols);
			return i;
		}
		bool success = funciones[i](cols->arr[i], ctx[i]);
		if (!success) {
			liberar_partes(cols);
			return i;
		}
		i++;
	}
	liberar_partes(cols);
	return i;
}

void cerrar_archivo_csv(struct archivo_csv *archivo)
{
	fclose(archivo->file);
	free(archivo);
}
