#include "tipo_jugador.h"
#include "tda_pokedex.h"

Jugador* jugador_crear() {
    Jugador* jug = calloc(1, sizeof(Jugador));
    if (jug == NULL) {
        return NULL;
    }
    jug->atrapados = pokedex_crear();
    if (jug->atrapados == NULL) {
        free(jug);
        return NULL;
    }
    jug->atrapados_max = pokedex_crear();
    if (jug->atrapados_max == NULL) {
        free(jug->atrapados);
        free(jug);
        return NULL;
    }
    jug->iteraciones = 0;
    jug->multiplicador_max = 1;
    jug->puntos = 0;
    jug->ultimo_movimiento = 0;

    return jug;
}

void jugador_destruir(Jugador* j) {
    if (j == NULL) {
        return;
    }
    poke_destruir(j->ultimo_capturado);
    pokedex_destruir(j->atrapados);
    pokedex_destruir(j->atrapados_max);
    free(j);
}
