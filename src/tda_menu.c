#include "tda_menu.h"
#include "hash/hash.h"

struct menu {
    Hash* opciones;
    Hash* acciones;
};

// Auxiliares:
bool imprimir_entrada(char* clave, void* valor, void* ctx);

// ---- INIT & DEINIT
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

void menu_destruir(Menu* m) {
    if (m == NULL) {
        return;
    }
    hash_destruir_todo(m->acciones, &free);
    hash_destruir(m->opciones);
    free(m);
}

// ---- PRINCIPALES
bool menu_agregar(Menu* m, char id, char* opcion, Fn f_accion) {
    if (m == NULL) {
        return false;
    }
    char s_id[2];
    s_id[0] = id;
    s_id[1] = '\0';
    hash_insertar(m->opciones, s_id, opcion, NULL);
    FuncAccion* fn = malloc(sizeof(FuncAccion));
    fn->accion = f_accion;
    hash_insertar(m->acciones, s_id, fn, NULL);
    return true;
}

bool menu_accion(Menu* m, char c, void* ctx) {
    if (c == 'q' || c == 'Q') {
        return false;
    }
    char s[2];
    s[0] = c;
    s[1] = '\0';
    FuncAccion* fn = hash_buscar(m->acciones, s);
    if (fn == NULL || fn->accion == NULL) {
        return false;
    }
    fn->accion(ctx);
    return true;
}

void menu_mostrar(Menu* m) {
    printf("Opciones: \n");
    hash_iterar(m->opciones, &imprimir_entrada, NULL);
}

// ---- AUXILIARES
bool imprimir_entrada(char* clave, void* valor, void* ctx) {
    char* descripcion = valor;

    printf("\t[%s]. %s\n", clave, descripcion);
    return true;
}
