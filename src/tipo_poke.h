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
    char* nombre;
    Color color;
    size_t puntos;
    size_t x;
    size_t y;
    char* patron;
} Poke;

Poke* poke_crear(char* nombre, size_t puntos, Color color, char* patron);

void poke_inicial_color(Poke* p, char* dest);

void poke_destruir(void*);

#endif
