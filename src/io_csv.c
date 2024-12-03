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
	if (!file) {
    	return NULL;
	}
	CSV *csv = malloc(sizeof(CSV));
	if (!csv) {
	   fclose(file);
	   return NULL;
	}

	csv->file = file;
	csv->sep = sep;
	return csv;
}

size_t csv_leer_linea(CSV *csv, size_t columnas, FnParse funcs[], void *ctx[])
{
	if (csv == NULL || csv->file == NULL) {
		return 0;
	}

	char buffer[MAX_LINEAS];
	char *resultado = fgets(buffer, sizeof(buffer), csv->file);
	if (!resultado)
		return 0;

	Vec *cols = dividir_string(buffer, csv->sep);

	size_t i = 0;
	while (cols->len <= columnas && i < columnas) {
		if (funcs[i] == NULL) {
			// if func is null should not continue
			liberar_partes(cols);
			return i;
		}
		bool ok = funcs[i](cols->arr[i], ctx[i]);
		if (!ok) {
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
    if (csv == NULL) {
        return;
    }
	fclose(csv->file);
	free(csv);
}
