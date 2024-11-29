#ifndef TIPO_JUGADOR
#define TIPO_JUGADOR

#include "tipos.h"
#include "tda_pokedex.h"
#include "tda_juego.h"

typedef struct jugador Jugador;
struct jugador {
    Poke* ultimo_capturado;
    Direccion ultimo_movimiento;
    Pokedex* combo_max;
    Pokedex* combo_actual;
    size_t multiplicador_max;
    size_t puntos;
    size_t iteraciones;
    size_t x;
    size_t y;
};

Jugador* jugador_crear();
Jugador* jugador_destruir(Jugador*);

#endif
