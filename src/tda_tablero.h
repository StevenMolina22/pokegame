#ifndef TDA_TABLERO
#define TDA_TABLERO

#include "tipos.h"
#include "tipo_jugador.h"
#include "tda_pokedex.h"

typedef struct tablero Tablero;

/**
 * Crea un tablero que guarda un jugador y una pokedex, para luego ser representados
 */
Tablero* tablero_crear(size_t ancho, size_t alto, Jugador* j, Pokedex* pkx);

/**
 * Limpia el tablero de cualquier elemento que tenga, dejandolo completamento vacio
 */
void tablero_vaciar(Tablero* t);

/**
 * Mueve el jugador en la direccion especificada si esta es valida
 * Actualiza ademas el estado interno como ultimo movimiento, sea o no valido
 */
void tablero_mover_jugador(Tablero* t, Direccion d);

/**
 * Mueve los pokemones de la pokedex del tablero respecto a cada patron que tiene
 * solo son movidos si este movimiento es valido
 */
void tablero_mover_pokes(Tablero* t);

/**
 * Verifica que el jugador haya captura el pokemon dado
 */
bool tablero_vericar_captura(Tablero* t, Poke* p);

/**
 * Destruye el tablero y todas las estructuras relacionados a este
 */
void tablero_destruir(Tablero* t);

#endif
