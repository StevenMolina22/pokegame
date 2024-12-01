#include "tipo_poke.h"
#include "io_csv.h"
#include "io_utils.h"
#include "tipos.h"

#define N_COLS 4

// INIT & DEINIT
Poke* poke_crear(char* nombre, size_t puntos, Color color, char* patron) {
    Poke* poke = malloc(sizeof(Poke));
    if (poke == NULL) {
        return NULL;
    }
    poke->nombre = nombre;
    poke->color = color;
    poke->puntos = puntos;
    poke->patron = patron;
    poke->x = (size_t)rand() % (ANCHO);
    poke->y = (size_t)rand() % (ALTO);
    return poke;
}

Poke* poke_copiar(Poke* p) {
    if (p == NULL) {
        return NULL;
    }
    Poke* nuevo = malloc(sizeof(Poke));
    if (nuevo == NULL) {
        return NULL;
    }
    nuevo->nombre = p->nombre;
    nuevo->color = p->color;
    nuevo->puntos = p->puntos;
    nuevo->patron = p->patron;
    nuevo->x = p->x;
    nuevo->y = p->y;
    return nuevo;
}

void poke_destruir(void* p) {
    free(p);
}

// UTILS
void poke_inicial_color(Poke* p, char* dest) {
    switch (p->color) {
        case Azul:
            sprintf(dest, "%s%c", ANSI_COLOR_BLUE, p->nombre[0]);
            break;
        case Amarillo:
            sprintf(dest, "%s%c", ANSI_COLOR_YELLOW, p->nombre[0]);
            break;
        case Magenta:
            sprintf(dest, "%s%c", ANSI_COLOR_MAGENTA, p->nombre[0]);
            break;
        case Verde:
            sprintf(dest, "%s%c", ANSI_COLOR_GREEN, p->nombre[0]);
            break;
        case Rojo:
            sprintf(dest, "%s%c", ANSI_COLOR_RED, p->nombre[0]);
            break;
        case Rosa:
            sprintf(dest, "%s%c", ANSI_COLOR_MAGENTA, p->nombre[0]);
            break;
    }
}

// IO & CSV
Poke *poke_leer(CSV *csv)
{
    FnParse funcs[] = { read_string, read_int, read_string, read_string};
	char* nombre = NULL;
	int puntos;
	char* color;
	char* patron;
	void* punteros[N_COLS] = { &nombre, &puntos, &color, &patron };

	if (csv_leer_linea(csv, N_COLS, funcs, punteros) != N_COLS) {
		// free(nombre); // Libera en caso de fallo
		return NULL;
	}

	Poke* pokemon = poke_crear(nombre, (size_t)puntos, color_desde(color), patron);
	return pokemon;
}

void poke_print(Poke* p, FILE* archivo) {
    fprintf(
        archivo,
        "Nombre: %s Puntos: %zu Color: %d Patron: %s",
        p->nombre, p->puntos, p->color, p->patron
    );
}
