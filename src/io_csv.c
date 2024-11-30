#include "io_csv.h"
#include <stdio.h>
#include <string.h>
#include "io_str_split.h"

#define MAX_LINEAS 1024

struct csv {
	char sep;
	FILE *file;
};

CSV *csv_abrir(const char *ruta, char sep)
{
	FILE *file = fopen(ruta, "r");
	if (!file)
		return NULL;

	struct csv *csv =
		(struct csv *)malloc(sizeof(struct csv));
	if (!csv)
		return NULL;

	csv->file = file;
	csv->sep = sep;
	return csv;
}

size_t csv_leer_linea(CSV *csv, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	if (csv == NULL || csv->file == NULL) {
		return 0;
	}

	char buffer[MAX_LINEAS];
	char *result = fgets(buffer, sizeof(buffer), csv->file);
	if (!result)
		return 0;

	Vec *cols = dividir_string(buffer, csv->sep);

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

FILE* csv_archivo(CSV* csv) {
    if (csv == NULL) {
        return NULL;
    }
    return csv->file;
}

void csv_cerrar(CSV *csv)
{
	fclose(csv->file);
	free(csv);
}
