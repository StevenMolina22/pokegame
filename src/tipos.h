#ifndef TIPOS_H
#define TIPOS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../extra/engine.h"
#include "../extra/ansi.h"

#define ANCHO 32
#define ALTO 15

#define ERROR -1

// ---- Movimiento
typedef enum tecla {
    TeclaArriba = TECLA_ARRIBA,
    TeclaAbajo = TECLA_ABAJO,
    TeclaDerecha = TECLA_DERECHA,
    TeclaIzquierda = TECLA_IZQUIERDA,
} Tecla;

typedef enum direccion {
    Arriba,
    Abajo,
    Derecha,
    Izquierda,
} Direccion;

// ---- Pokemones
typedef enum patron {
    PatronArriba      = 'N',
    PatronAbajo       = 'S',
    PatronDerecha     = 'E',
    PatronIzquierda   = 'O',
    PatronEspejo      = 'J',
    PatronInverso     = 'I',
    PatronRandom      = 'R',
} Patron;

typedef enum color {
    Rojo,
    Azul,
    Rosa,
    Amarillo,
    Magenta,
    Verde,
} Color;


// Conversores
Color color_desde(char* s);
void str_desde(Color color, char* s);
Direccion patron_a_direccion(Patron p);
Direccion tecla_a_direccion(Tecla t);

#endif
