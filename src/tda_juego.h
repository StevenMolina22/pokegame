#ifndef TDA_JUEGO
#define TDA_JUEGO

typedef struct juego Juego;

#include "tda_pokedex.h"
#include "tda_tablero.h"
#include "tda_tablero_priv.h"
#include <stdio.h>

// TODO! eliminar esta funcion
//
Jugador* juego_jugador(Juego* j);

/**
 * Crea la estructura para el juego
 */
Juego* juego_crear();

/**
 * Inicia las condiciones necesarias para el juego
 */
void juego_iniciar(Juego* j);

/**
 * Realiza las acciones y los movimientos del juego
 */
void juego_correr(Juego* j, int entrada);

/**
 * Termina el juego
 */
void juego_terminar(Juego* j);

/**
 * Muestra las estadisticas que tuvo el jugador
 */
void juego_mostrar_resultados(Juego* j);

/**
 * Destruye el juego y todas las estructuras relacionadas con este
 */
void juego_destruir(Juego* j);

#endif
