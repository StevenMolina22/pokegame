#ifndef TIPO_POKE_H
#define TIPO_POKE_H

#include "tipos.h"

typedef enum color {
    Rojo,
    Azul,
    Rosa,
    Amarillo,
    Magenta,
    Verde,
} Color;

typedef struct poke {
    char nombre[100];
    Color color;
    size_t puntos;
    size_t x;
    size_t y;
    char patron[100];
} Poke;

Poke* poke_crear();

void poke_destruir(Poke*);

#endif
