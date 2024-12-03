#include "tda_juego.h"
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


    juego->pokedex = pokedex_crear();
    if (juego->pokedex == NULL) {
        free(juego);
        return NULL;
    }

    juego->tablero = tablero_crear(ANCHO, ALTO);
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
    if (!pokedex_cargar_desde(j->pokedex, csv)){
        return;
    };

    size_t i = 0;
    size_t pkx_len = pokedex_len(j->pokedex);
    while (i < N_POKES_TABLERO && i < pkx_len) {
        size_t idx = (size_t)rand() % pkx_len;
        Poke* p;
        lista_obtener(pokedex_lista(j->pokedex), idx, (void**)&p);
        pokedex_agregar(pkx, poke_copiar(p));
        i++;
    }
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

    printf("Puntaje alzanzado: %zu\n", jug->puntos);
    printf("Maximo multiplicador: %zu\n", jug->multiplicador_max);
    // TODO!
    // printf("Cadena mas larga: \n");
    printf("Maximo cantidad de combo: %zu\n", jug->max_cant_combo);
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
        jug->cant_combo++;
        if (jug->cant_combo > jug->max_cant_combo) {
            jug->max_cant_combo = jug->cant_combo;
        }
    } else {
        jug->cant_combo = 0;
        jug->multiplicador = 1;
        // jug->ultimo_capturado = NULL; ??? Remove or let be?
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
