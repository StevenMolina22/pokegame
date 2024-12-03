#include "tipo_poke.h"

#define N_COLS 4

// INIT & DEINIT
Poke* poke_crear(char* nombre, size_t puntos, Color color, char* patron) {
    Poke* poke = calloc(1, sizeof(Poke));
    if (poke == NULL) {
        return NULL;
    }
    poke->nombre = str_copy(nombre);
    if (poke->nombre == NULL) {
        free(poke);
        return NULL;
    }
    poke->patron = str_copy(patron);
    if (poke->patron == NULL) {
        free(poke->nombre);
        free(poke);
        return NULL;
    }
    poke->color = color;
    poke->puntos = puntos;
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
    nuevo->nombre = str_copy(p->nombre);
    if (nuevo->nombre == NULL) {
        free(nuevo);
        return NULL;
    }
    nuevo->patron = str_copy(p->patron);
    if (nuevo->patron == NULL) {
        free(nuevo->nombre);
        free(nuevo);
        return NULL;
    }
    nuevo->color = p->color;
    nuevo->puntos = p->puntos;
    nuevo->x = p->x;
    nuevo->y = p->y;
    return nuevo;
}

void poke_destruir(Poke* p) {
    if (p == NULL) {
        return;
    }
    free(p->nombre);
    free(p->patron);
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
		return NULL;
	}

	Poke* pokemon = poke_crear(nombre, (size_t)puntos, color_desde(color), patron);
	free(nombre);
	free(patron);
	free(color);
	return pokemon;
}

void poke_print(Poke* p, FILE* archivo) {
    char s[100];
    str_desde(p->color, s);
    fprintf(
        archivo,
        "Nombre: %s Puntos: %zu Color: %s Patron: %s\n",
        p->nombre, p->puntos, s, p->patron
    );
}
