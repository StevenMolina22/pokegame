#ifndef TDA_POKEDEX
#define TDA_POKEDEX

#include "tipo_poke.h"
#include "tipos.h"
#include "lista/lista.h"
#include "abb/abb.h"
#include "io/io_csv.h"

typedef struct pokedex Pokedex;
typedef struct it_pokedex ItPokedex;


// ---- INIT & DEINIT

/**
 * Crea una nueva pokedex
 */
Pokedex* pokedex_crear();
/**
 * Destruye la pokedex y todas las estructuras asociadas a esta
 */
void pokedex_destruir(Pokedex* pkx);
/**
 * Copia una pokedex a otra (deep copy)
 */
Pokedex* pokedex_copiar(Pokedex* pkx);



// ---- MAIN

/**
 * Agrega un pokemon a la pokedex
 */
bool pokedex_agregar(Pokedex* pkx, Poke* p);
/**
 * Vacia la pokedex de todos sus pokemones
 */
bool pokedex_vaciar(Pokedex* pkx);
/**
 * Agrega un pokemon random a la pokedex
 */
bool pokedex_agregar_random(Pokedex* pkx_desde, Pokedex* pkx_hasta);



// ---- GETTERS

/**
 * Devuelve la cantidad de pokemones en la pokedex
 */
size_t pokedex_cant(Pokedex* pkx);
/**
 * Devuelve una lista con todos los pokemones de la pokedex
 */
Lista* pokedex_lista(Pokedex* pkx);



// ---- IO & CSV

/**
 *
 */
void pokedex_print(Pokedex* pkx, FILE* archivo);
/**
 *
 */
void pokedex_print_nombres(Pokedex* pkx, FILE* archivo);
/**
 * Agrega los pokemones desde un archivo a una pokedex ya creada
 */
bool pokedex_cargar_desde(Pokedex* pkx, CSV* csv);

#endif
