#include "tda_menu.h"
#include "hash.h"
#include <stdio.h>

typedef bool (*Fn)(void* ctx);

bool imprimir_entrada(char* clave, void* valor, void* ctx) {
    char* descripcion = valor;

    printf("\t%s. %s\n", clave, descripcion);
    return true;
}

struct menu {
    Hash* opciones;
    Hash* acciones;
};

Menu* menu_crear() {
    Menu* m = malloc(sizeof(Menu));
    if (m == NULL) {
        return NULL;
    }

    Hash* opciones = hash_crear(8);
    if (opciones == NULL) {
        free(m);
        return NULL;
    }

    Hash* acciones = hash_crear(8);
    if (acciones == NULL) {
        free(m);
        free(opciones);
        return NULL;
    }

    m->acciones = acciones;
    m->opciones = opciones;
    return m;
}

bool menu_accion(Menu* m, char c) {
    if (c == 'q' || c == 'Q') {
        return false;
    }
    char s[2];
    s[0] = c;
    s[1] = '\0';
    Fn fn = (Fn)hash_buscar(m->acciones, s);
    if (fn == NULL) {
        return false;
    }
    fn(NULL);
    return true;
}

void menu_mostrar(Menu* m) {
    printf("Optiones: \n");
    hash_iterar(m->opciones, &imprimir_entrada, NULL);
}

void menu_destruir(Menu* m) {
    if (m == NULL) {
        return;
    }
    hash_destruir(m->acciones);
    hash_destruir(m->opciones);
    free(m);
}

// FUNCIONES PARA ACCIONES
bool mostrar_pokedex(void* ctx);
bool juego_jugar(void* ctx);
bool juego_juegar_semilla(void* ctx);
bool salir(void* ctx);
