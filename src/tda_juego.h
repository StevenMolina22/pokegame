#ifndef TDA_JUEGO
#define TDA_JUEGO

typedef struct juego Juego;

#include "tda_pokedex.h"
#include "tda_tablero.h"
#include "tda_tablero_priv.h"
#include <stdio.h>

// ---- INIT & DEINIT

/**
 * Crea la estructura para el juego
 */
Juego* juego_crear();
/**
 * Destruye el juego y todas las estructuras relacionadas con este
 */
void juego_destruir(Juego* j);



// ---- PRINCIPALES

/**
 * Inicia las condiciones necesarias para el juego
 */
void juego_iniciar(Juego* j, CSV* csv);
/**
 * Realiza las acciones y los movimientos del juego
 */
void juego_correr(Juego* j, int entrada);
/**
 * Muestra las estadisticas que tuvo el jugador
 */
void juego_mostrar_resultados(Juego* j);



// ---- GETTERS

/**
 * Devuelve el tiempo en el que se empezo el juego
 */
time_t juego_tiempo_inicio(Juego* j);

#endif
