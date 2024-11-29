#include "tda_juego.h"
#include "tda_pokedex.h"
#include "tda_tablero.h"
#include "tda_tablero_priv.h"
#include <stdio.h>

struct juego {
    Tablero* tablero;
    size_t semilla;
};

// ---- FUNCIONES AUXILIARES
void procesar_entrada(Juego* j, Direccion d);
void verificar_capturas(Juego* j);
void actualizar_captura(Juego* j, Poke* p);

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
    Pokedex* pkx = tablero_pokedex(j->tablero);
    pokedex_spawn(pkx);
}

void juego_correr(Juego* j, int entrada) {
    procesar_entrada(j, tecla_a_direccion(entrada));
    verificar_capturas(j);
    tablero_mostrar(j->tablero);
}

void juego_terminar(Juego* j) {
}

void juego_mostrar_resultados(Juego* j) {
    Jugador* jug = tablero_jugador(j->tablero);
    printf("Cadena mas larga: \n");
    // iterar y mostrar pokemones de j->board->player->cadena_max
    printf("Maximos puntos: %zu\n", jug->puntos);
    printf("Maximo multiplicador: %zu\n", jug->multiplicador_max);
}

void juego_destruir(Juego* j) {
}

// ---- FUNCIONES AUXILIARES
void procesar_entrada(Juego* j, Direccion d) {
    if (d != Arriba && d != Abajo && d != Derecha && d != Izquierda) {
        return;
    }
    tablero_mover_jugador(j->tablero, d);
    tablero_mover_pokes(j->tablero);
}

void verificar_capturas(Juego* j) {
    // TODO!: Elegir como se va encontrar y eliminar el pokemon capturado
    // NOTA: A tener en cuenta el hecho de iterar y eliminar a la vez
    //      o el hecho de iterar primero y buscar todos para luego eliminar
}

void actualizar_captura(Juego* j, Poke* p) {
    Jugador* jug = tablero_jugador(j->tablero);
    Poke* ultimo = jug->ultimo_capturado;

    if (ultimo == NULL || ultimo->nombre[0] == p->nombre[0] || ultimo->color == p->color) {
        jug->multiplicador++;
        pokedex_agregar(jug->combo_actual, p);
        size_t actual_len = pokedex_len(jug->combo_actual);
        size_t max_len = pokedex_len(jug->combo_max);
        if (actual_len > max_len) {
            jug->combo_max = jug->combo_actual;
        }
    } else {
        jug->multiplicador = 1;
        pokedex_vaciar(jug->combo_actual);
    }

    if (jug->multiplicador > jug->multiplicador_max) {
        jug->multiplicador_max = jug->multiplicador;
    }

    jug->puntos += jug->multiplicador * p->puntos;
    jug->ultimo_capturado = p;
}
