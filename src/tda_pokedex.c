#include "tda_pokedex.h"
#include "tipo_poke.h"

struct pokedex {
    Lista* pokes;
};

// struct it_pokedex {
// };

int cmp(void *, void *); // TODO!: Implementar funcion

/**
 * Crea una nueva pokedex
 */
Pokedex* pokedex_crear() {
    Pokedex* pkx = malloc(sizeof(Pokedex));
    Lista* l = lista_crear();
    if (l == NULL) {
        free(pkx);
        return NULL;
    }
    pkx->pokes = l;
    return pkx;
}

/**
 * Agrega los pokemones desde un archivo a una pokedex ya creada
 */
void pokedex_carga_desde(Pokedex* pkx, char* archivo) {
}

/**
 * Agrega un pokemon a la pokedex
 */
void pokedex_agregar(Pokedex* pkx, Poke* p) {
    if (pkx == NULL) {
        return;
    }
    lista_agregar_final(pkx->pokes, p);
}

/**
 * Remueve el pokemon del indice especificado de la pokedex
 */
void pokedex_remover(Pokedex* pkx, size_t idx) {
    if (pkx == NULL) {
        return;
    }
    // TODO!: Analizar si logica remover es necesaria, de ser asi analizar como implementar
    // lista_
}

/**
 * Vacia la pokedex de todos sus pokemones
 */
void pokedex_vaciar(Pokedex* pkx) {
    if (pkx == NULL) {
        return;
    }
    lista_destruir_todo(pkx->pokes, &poke_destruir);
    Lista* l = lista_crear();
    if (l == NULL) {
        return;
    }
    pkx->pokes = l;
}

/**
 * Devuelve la cantidad de pokemones en la pokedex
 */
size_t pokedex_len(Pokedex* pkx) {
    if (pkx == NULL) {
        return 0;
    }
    return lista_len(pkx->pokes);
}

/**
 * Devuelve una lista de todos los pokemones
 */
Lista* pokedex_lista(Pokedex* pkx) {
    if (pkx == NULL) {
        return NULL;
    }
    return pkx->pokes;
}

/**
 * Agrega una cantidad n de pokemones a la pokedex
 */
void pokedex_spawn(Pokedex* pkx) {
    Poke* p1 = poke_crear("Pikachu", 15, Amarillo, "I");
    Poke* p2 = poke_crear("Pikachu", 15, Amarillo, "J");
    Poke* p3 = poke_crear("Lapras", 15, Azul, "NRORSRER");
    pokedex_agregar(pkx, p1);
    pokedex_agregar(pkx, p2);
    pokedex_agregar(pkx, p3);
}

/**
 * Agrega un pokemon random a la pokedex
 */
void pokedex_agregar_random(Pokedex* pkx) {
}

/**
 * Destruye la pokedex y todas las estructuras asociadas a esta
 */
void pokedex_destuir(Pokedex* pkx) {
}
