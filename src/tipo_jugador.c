#include "tipo_jugador.h"
#include "tda_pokedex.h"

Jugador* jugador_crear() {
    Jugador* jugador = calloc(1, sizeof(Jugador));
    if (jugador == NULL) {
        return NULL;
    }

    // TODO!: Agregar todos los atributos para jugador
    Pokedex* pkx = pokedex_crear();
    if (pkx == NULL) {
        free(jugador);
        free(pkx);
    }

    jugador->combo_actual = pkx;
    jugador->combo_max = pkx;
    jugador->iteraciones = 0;
    jugador->multiplicador_max = 1;
    jugador->puntos = 0;
    jugador->ultimo_movimiento = 0; // TODO!: Verificar esta inicializacion de enum

    return jugador;
}

void jugador_destruir(Jugador* j) {
    pokedex_destruir(j->combo_max);
    pokedex_destruir(j->combo_actual);
    free(j);
}
