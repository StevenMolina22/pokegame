#include "tda_tablero.h"

// firmas de funciones auxiliares
char** matriz_crear(size_t ancho, size_t alto);

struct tablero {
    // char arr[ANCHO][ALTO];
    char** matriz;
    Jugador* jugador;
    Pokedex* pokes;
    size_t ancho;
    size_t alto;
    // TODO!: Verifica si agregar atributos de tiempo
};

Tablero* tablero_crear(size_t ancho, size_t alto, Jugador* jugador, Pokedex* pkx) {
    Tablero* t = malloc(sizeof(Tablero));
    if (t == NULL) {
        return NULL;
    }
    char** matriz = matriz_crear(ancho, alto);
    if (matriz == NULL) {
        free(t);
        return NULL;
    }
    t->matriz = matriz;
    t->jugador = jugador;
    t->pokes = pkx;
    t->ancho = ancho;
    t->alto = alto;
    return t;
}

void tablero_vaciar(Tablero* t) {
}

void tablero_agregar_poke(Tablero* t) {
}

void tablero_verificar_capturas(Tablero* t) {
}

void tablero_destruir(Tablero* t) {
}

// ---- FUNCIONES AUXILIARES
char** matriz_crear(size_t ancho, size_t alto) {
    char** m = malloc(alto * sizeof(char*));
    if (m == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < alto; i++) {
        char* temp = malloc(ancho * sizeof(char));
        if (temp == NULL) {
            return NULL;
        }
        m[i] = temp;
    }
    return m;
}
