#include "tipo_poke.h"

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

void poke_inicial_color(Poke* p, char* dest) {
    switch (p->color) {
        case Azul:
            sprintf(dest, "%s%c", ANSI_COLOR_BLUE, p->nombre[0]);
            break;
        case Amarillo:
            sprintf(dest, "%s%c", ANSI_COLOR_BLUE, p->nombre[0]);
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

void poke_destruir(void* p) {
    free(p);
}
