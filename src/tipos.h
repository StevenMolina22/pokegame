#ifndef TIPOS_H
#define TIPOS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define ANCHO 32
#define ALTO 15

typedef enum direccion {
    Arriba      = 'W',
    Abajo       = 'S',
    Derecha     = 'A',
    Izquierda   = 'D',
} Direccion;

typedef enum patron {
    PokeArriba      = 'N',
    PokeAbajo       = 'S',
    PokeIzquierda   = 'E',
    PokeDerecha     = 'O',
    PokeEspejo      = 'J',
    PokeInverso     = 'I',
    PokeRandom      = 'R',
} Patron;

#endif
