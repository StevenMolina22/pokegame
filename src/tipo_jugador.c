#include "tipo_jugador.h"
#include "tipo_poke.h"

Jugador* jugador_crear() {
    Jugador* jugador = calloc(1, sizeof(Jugador));
    if (jugador == NULL) {
        return NULL;
    }
    jugador->iteraciones = 0;
    jugador->multiplicador_max = 1;
    jugador->puntos = 0;
    jugador->ultimo_movimiento = 0;

    return jugador;
}

void jugador_destruir(Jugador* j) {
    if (j == NULL) {
        return;
    }
    poke_destruir(j->ultimo_capturado);
    free(j);
}
