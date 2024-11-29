#include "tda_tablero.h"
#include "tda_tablero_priv.h"
#include "tipo_poke.h"


// ---- INTERFAZ TDA
// INIT & DEINIT
Tablero* tablero_crear(size_t ancho, size_t alto, Jugador* jugador, Pokedex* pkx) {
    Tablero* t = calloc(1, sizeof(Tablero));
    if (t == NULL) {
        return NULL;
    }
    // TODO!: Verificar que la asignacion del string no rompa por temas de stack y stack frames
    for (size_t i = 0; i < alto; i++) {
        for (size_t j = 0; j < ancho; j++) {
            // char* s = malloc(100 * sizeof(char));
            // s = " ";
            t->matriz[i][j] = " ";
        }
    }
    t->jugador = jugador;
    t->pokes = pkx;
    t->ancho = ancho;
    t->alto = alto;
    return t;
}

void tablero_destruir(Tablero* t) {
    if (t == NULL) {
        return;
    }
    jugador_destruir(t->jugador);
    pokedex_destuir(t->pokes);
    free(t);
}

// GENERALES
void tablero_vaciar(Tablero* t) {
    if (t == NULL) {
        return;
    }
    for (size_t i = 0; i < ALTO; i++) {
        for (size_t j = 0; j < ANCHO; j++) {
            t->matriz[i][j] = " ";
        }
    }
}

bool tablero_esta_capturado(Tablero* t, Poke* p) {
    if (t == NULL) {
        return false;
    }
    return t->jugador->x == p->x && t->jugador->y == p->y;
}

// IO
void tablero_mostrar(Tablero* t) {
    if (t == NULL) {
        return;
    }
    tablero_vaciar(t);
    size_t x = t->jugador->x;
    size_t y = t->jugador->y;
    t->matriz[y][x] = ANSI_COLOR_MAGENTA ANSI_COLOR_BOLD "Ω";

    // pokemones
    ListaIt* it = lista_it_crear(pokedex_lista(t->pokes));
    while (lista_it_hay_siguiente(it)) {
        Poke* p = lista_it_actual(it);
        char s[100];
        poke_inicial_color(p, s);
        t->matriz[p->y][p->x] = s;
        lista_it_avanzar(it);
    }
    lista_it_destruir(it);

    matriz_print(t->matriz);
}

// GETTERS
Jugador* tablero_jugador(Tablero* t) {
    if (t == NULL) {
        return NULL;
    }
    return t->jugador;
}

Pokedex* tablero_pokedex(Tablero* t) {
    if (t == NULL) {
        return NULL;
    }
    return t->pokes;
}


// ---- FUNCIONES AUXILIARES
void matriz_print(str_t m[ALTO][ANCHO]) {
    for (size_t j = 0; j < ANCHO + 2; j++) {
        printf("%s", ANSI_COLOR_WHITE ANSI_COLOR_BOLD "*");
    }
    printf("\n");
    for (size_t i = 0; i < ALTO; i++) {
        printf("%s", ANSI_COLOR_WHITE ANSI_COLOR_BOLD "*");
        for (size_t j = 0; j < ANCHO; j++) {
            printf("%s", m[i][j]);
        }
        printf("%s", ANSI_COLOR_WHITE ANSI_COLOR_BOLD "*");
        printf("\n");
    }
    for (size_t j = 0; j < ANCHO + 2; j++) {
        printf("%s", ANSI_COLOR_WHITE ANSI_COLOR_BOLD "*");
    }
    printf("\n");
}
