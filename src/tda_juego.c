#include "tda_juego.h"
#include "tda_pokedex.h"
#include "tda_tablero.h"
#include "tipo_poke.h"
#include "lista/lista.h"

struct juego {
    Tablero* tablero;
    size_t semilla;
    time_t tiempo_inicio;
};

// ---- FUNCIONES AUXILIARES
void procesar_entrada(Juego* j, Direccion d);
void verificar_capturas(Juego* j);
void actualizar_captura(Juego* j, Poke* p);

Juego* juego_crear() {
    Juego* juego = calloc(1, sizeof(Juego));
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
    if (juego->tablero == NULL) {
        return NULL;
    }
    juego->tiempo_inicio = time(NULL);
    return juego;
}

void juego_iniciar(Juego* j, CSV* csv) {
    Pokedex* pkx = tablero_pokedex(j->tablero);
    pokedex_cargar_desde(pkx, csv);
}

void juego_correr(Juego* j, int entrada) {
    procesar_entrada(j, tecla_a_direccion(entrada));
    verificar_capturas(j);
    // pokedex_print(tablero_pokedex(j->tablero), stdout);
    tablero_mostrar(j->tablero);
}

void juego_terminar(Juego* j) {
}

void juego_mostrar_resultados(Juego* j) {
    Jugador* jug = tablero_jugador(j->tablero);

    printf("Cadena mas larga: \n");
    pokedex_print(jug->combo_max, stdout);

    printf("Maximos puntos: %zu\n", jug->puntos);
    printf("Maximo multiplicador: %zu\n", jug->multiplicador_max);
}

void juego_destruir(Juego* j) {
    if (j == NULL) {
        return;
    }
    tablero_destruir(j->tablero);
    free(j);
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
    size_t i = 0;
    Pokedex* pkx = tablero_pokedex(j->tablero);
    Lista* l = pokedex_lista(pkx);
    ListaIt* it = lista_it_crear(l);

    while (lista_it_hay_siguiente(it)) {
        Poke* p = lista_it_actual(it);
        lista_it_avanzar(it);
        if (tablero_esta_capturado(j->tablero, p)) {
            // TODO!: Solucionar problemas de memoria en esta seccion
            actualizar_captura(j, p);
            lista_remover(l, i, NULL);
            pokedex_agregar_random(pkx);
        } else {
            i++;
        }
    }
    lista_it_destruir(it);
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
            pokedex_destruir(jug->combo_max);
            jug->combo_max = pokedex_copiar(jug->combo_actual);
        }
    } else {
        // HAY FUGAS DE MEMORIA EN ESTE BLOQUE
        pokedex_destruir(jug->combo_actual);
        jug->combo_actual = pokedex_crear();
        jug->multiplicador = 1;
        jug->ultimo_capturado = NULL;
    }

    if (jug->multiplicador > jug->multiplicador_max) {
        jug->multiplicador_max = jug->multiplicador;
    }

    jug->puntos += jug->multiplicador * p->puntos;
    jug->ultimo_capturado = p;
}

// TODO! Eliminar esta funcion
Jugador* juego_jugador(Juego* j) {
    return tablero_jugador(j->tablero);
}

time_t juego_tiempo_inicio(Juego* j) {
    if (j == NULL) {
        return 0;
    }
    return j->tiempo_inicio;
}
