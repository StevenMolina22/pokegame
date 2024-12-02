#include "tipo_jugador.h"
// #include "lista/lista.h"

Jugador* jugador_crear() {
    Jugador* jugador = calloc(1, sizeof(Jugador));
    if (jugador == NULL) {
        return NULL;
    }
    // jugador->atrapados = lista_crear(); // nombre de los atrapados
    // if (jugador->atrapados == NULL) {
    //     free(jugador);
    //     return NULL;
    // }
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
    // pokedex_destruir(j->combo_max);
    // pokedex_destruir(j->combo_actual);
    // lista_destruir_todo(j->atrapados, free);
    free(j);
}
