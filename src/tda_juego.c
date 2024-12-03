#include "tda_juego.h"
// #include "io/io_utils.h"
#include "tda_pokedex.h"
#include "tda_tablero.h"
#include "tipo_poke.h"
#include "lista/lista.h"

#define N_POKES_TABLERO 7

struct juego {
    Tablero* tablero;
    Pokedex* pokedex;
    size_t semilla;
    time_t tiempo_inicio;
};

// ---- FUNCIONES AUXILIARES
void procesar_entrada(Juego* j, Direccion d);
void verificar_capturas(Juego* j);
void actualizar_captura(Juego* j, Poke* p);

// ---- INIT & DEINIT
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

    Pokedex* pkx_tablero = pokedex_crear();
    if (pkx_tablero == NULL) {
        free(juego);
        free(jugador);
        return NULL;
    }

    juego->pokedex = pokedex_crear();
    if (juego->pokedex == NULL) {
        free(juego);
        free(jugador);
        free(pkx_tablero);
        return NULL;
    }

    juego->tablero = tablero_crear(ANCHO, ALTO, jugador, pkx_tablero);
    if (juego->tablero == NULL) {
        return NULL;
    }
    juego->tiempo_inicio = time(NULL);
    return juego;
}

void juego_destruir(Juego* j) {
    if (j == NULL) {
        return;
    }
    tablero_destruir(j->tablero);
    pokedex_destruir(j->pokedex);
    free(j);
}


// ---- PRINCIPALES
void juego_iniciar(Juego* j, CSV* csv) {
    if (j == NULL) {
        return;
    }
    Pokedex* pkx = tablero_pokedex(j->tablero);
    pokedex_cargar_desde(j->pokedex, csv);

    size_t i = 0;
    size_t pkx_len = pokedex_len(j->pokedex);
    while (i < N_POKES_TABLERO && i < pkx_len) {
        size_t idx = (size_t)rand() % pkx_len;
        Poke* p;
        lista_obtener(pokedex_lista(j->pokedex), idx, (void**)&p);
        pokedex_agregar(pkx, poke_copiar(p));
        i++;
    }
    // ListaIt* it = lista_it_crear(pokedex_lista(j->pokedex));
    // size_t i = 0;
    // while (lista_it_hay_siguiente(it)) {
    //     if (i == N_POKES_TABLERO) {
    //         break;
    //     }
    //     Poke* p = lista_it_actual(it);
    //     pokedex_agregar(pkx, poke_copiar(p));
    //     lista_it_avanzar(it);
    //     i++;
    // }
    // lista_it_destruir(it);
}

void juego_correr(Juego* j, int entrada) {
    if (j == NULL) {
        return;
    }
    procesar_entrada(j, tecla_a_direccion(entrada));
    verificar_capturas(j);
    tablero_mostrar(j->tablero);
}

void juego_mostrar_resultados(Juego* j) {
    if (j == NULL) {
        return;
    }
    Jugador* jug = tablero_jugador(j->tablero);

    printf("Cadena mas larga: \n");
    printf("Maximos puntos: %zu\n", jug->puntos);
    printf("Maximo multiplicador: %zu\n", jug->multiplicador_max);
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
    // Jugador* jug = tablero_jugador(j->tablero);

    while (lista_it_hay_siguiente(it)) {
        Poke* p = lista_it_actual(it);
        lista_it_avanzar(it);
        if (tablero_esta_capturado(j->tablero, p)) {
            // if (jug->ultimo_capturado == p) {
            //     jug->ultimo_capturado = NULL;
            // }
            lista_remover(l, i, NULL);
            actualizar_captura(j, p);
            poke_destruir(p);
            pokedex_agregar_random(j->pokedex, pkx);
        } else {
            i++;
        }
    }
    lista_it_destruir(it);
}

void actualizar_captura(Juego* j, Poke* p) {
    Jugador* jug = tablero_jugador(j->tablero);
    Poke* ultimo = jug->ultimo_capturado;

    if (
        ultimo == NULL ||
        ultimo->nombre[0] == p->nombre[0] ||
        ultimo->color == p->color
    ) {
        jug->multiplicador++;
        if (ultimo == NULL) {
            jug->cant_combo = 0; // si es null
        }
        jug->cant_combo++;
        if (jug->cant_combo > jug->max_cant_combo) {
            jug->max_cant_combo = jug->cant_combo;
        }
    } else {
        jug->cant_combo = 0;
        jug->multiplicador = 1;
        // jug->ultimo_capturado = NULL;
    }

    if (jug->multiplicador > jug->multiplicador_max) {
        jug->multiplicador_max = jug->multiplicador;
    }

    jug->puntos += jug->multiplicador * p->puntos;

    poke_destruir(jug->ultimo_capturado);
    jug->ultimo_capturado = poke_copiar(p);
}

// ---- GETTERS
time_t juego_tiempo_inicio(Juego* j) {
    if (j == NULL) {
        return 0;
    }
    return j->tiempo_inicio;
}
