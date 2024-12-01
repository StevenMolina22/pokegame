#include "tipo_jugador.h"
#include "tda_pokedex.h"

Jugador* jugador_crear() {
    Jugador* jugador = calloc(1, sizeof(Jugador));
    if (jugador == NULL) {
        return NULL;
    }

    // TODO!: Agregar todos los atributos para jugador
    Pokedex* combo_actual = pokedex_crear();
    if (combo_actual == NULL) {
        free(jugador);
    }
    Pokedex* combo_max = pokedex_crear();
    if (combo_max == NULL) {
        free(combo_max);
        free(jugador);
    }

    jugador->combo_actual = combo_actual;
    jugador->combo_max = combo_max;
    jugador->iteraciones = 0;
    jugador->multiplicador_max = 1;
    jugador->puntos = 0;
    jugador->ultimo_movimiento = 0; // TODO!: Verificar esta inicializacion de enum

    return jugador;
}

void jugador_destruir(Jugador* j) {
    if (j == NULL) {
        return;
    }
    pokedex_destruir(j->combo_max);
    pokedex_destruir(j->combo_actual);
    free(j);
}
