#include "tda_juego.h"
#include "tda_pokedex.h"
#include "tda_tablero.h"

struct juego {
    Tablero* tablero;
    size_t semilla;
};

Juego* juego_crear() {
    Juego* juego = malloc(sizeof(Juego));
    if (juego == NULL) {
        return NULL;
    }

    Jugador* jugador = jugador_crear();
    if (jugador == NULL) {
        free(juego);
        return NULL;
    }

    Pokedex* pkx = pokedex_crear();
    if (pkx == NULL) {
        free(juego);
        free(jugador);
        return NULL;
    }

    juego->tablero = tablero_crear(ANCHO, ALTO, jugador, pkx);
    return juego;
}

void juego_iniciar(Juego* j) {
}

void juego_correr(Juego* j, int entrada) {
}

void juego_terminar(Juego* j) {
}

void juego_mostrar_resultados(Juego* j) {
}

void juego_destruir(Juego* j) {
}
