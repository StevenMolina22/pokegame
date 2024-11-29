#ifndef TDA_POKEDEX
#define TDA_POKEDEX

#include "tipo_poke.h"
#include "tipos.h"

typedef struct pokedex Pokedex;

/**
 * Crea una nueva pokedex
 */
Pokedex* pokedex_crear();

/**
 * Agrega los pokemones desde un archivo a una pokedex ya creada
 */
void pokedex_carga_desde(Pokedex* pkx, char* archivo);

/**
 * Agrega un pokemon a la pokedex
 */
void pokedex_agregar(Pokedex* pkx, Poke* p);

/**
 * Remueve el pokemon del indice especificado de la pokedex
 */
void pokedex_remover(Pokedex* pkx, size_t idx);

/**
 * Vacia la pokedex de todos sus pokemones
 */
void pokedex_vaciar(Pokedex* pkx);

/**
 * Devuelve la cantidad de pokemones en la pokedex
 */
void pokedex_len(Pokedex* pkx);

/**
 * Devuelve una lista de todos los pokemones
 */
void pokedex_lista(Pokedex* pkx);

/**
 * Agrega una cantidad n de pokemones a la pokedex
 */
void pokedex_spawn(Pokedex* pkx);

/**
 * Agrega un pokemon random a la pokedex
 */
void pokedex_agregar_random(Pokedex* pkx);

/**
 * Destruye la pokedex y todas las estructuras asociadas a esta
 */
void pokedex_destuir(Pokedex*);

#endif
