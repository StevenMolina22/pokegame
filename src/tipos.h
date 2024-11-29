#ifndef TIPOS_H
#define TIPOS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../extra/engine.h"

#define ANCHO 32
#define ALTO 15

#define ERROR -1

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

typedef enum patron {
    PatronArriba      = 'N',
    PatronAbajo       = 'S',
    PatronIzquierda   = 'E',
    PatronDerecha     = 'O',
    PatronEspejo      = 'J',
    PatronInverso     = 'I',
    PatronRandom      = 'R',
} Patron;

#endif
