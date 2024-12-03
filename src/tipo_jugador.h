#ifndef TIPO_JUGADOR
#define TIPO_JUGADOR

#include "tipos.h"
#include "tda_pokedex.h"

typedef struct jugador Jugador;
struct jugador {
    Poke* ultimo_capturado;
    Direccion ultimo_movimiento;
    Pokedex* atrapados; // nombre de los pokemones atrapados
    Pokedex* atrapados_max;
    size_t max_cant_combo;
    size_t cant_combo;
    size_t multiplicador_max;
    size_t multiplicador;
    size_t puntos;
    size_t iteraciones;
    size_t x;
    size_t y;
};

Jugador* jugador_crear();
void jugador_destruir(Jugador*);

#endif
