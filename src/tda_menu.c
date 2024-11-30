#include "tda_menu.h"
#include "hash.h"

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

bool menu_agregar(Menu* m, char id, char* opcion, Fn f_accion) {
    if (m == NULL) {
        return false;
    }
    char s_id[2];
    s_id[0] = id;
    s_id[1] = '\0';
    hash_insertar(m->opciones, s_id, opcion, NULL);
    // TODO!: Limpia este malloc
    FuncAccion* fn = malloc(sizeof(FuncAccion));
    fn->accion = f_accion;
    hash_insertar(m->acciones, s_id, fn, NULL);
    return true;
}

bool menu_accion(Menu* m, char c, void* ctx) {
    // TODO!: Elimininar prints
    // printf("Adentro de accion\n");
    if (c == 'q' || c == 'Q') {
        return false;
    }
    char s[2];
    s[0] = c;
    s[1] = '\0';
    // printf("Antes de hash buscar \n");
    FuncAccion* fn = hash_buscar(m->acciones, s);
    // printf("Despues de hash buscar \n");
    // NOTA ERROR: fn->accion es una funcion incorrecta
    if (fn == NULL || fn->accion == NULL) {
        // printf("No fn o fn->accion\n");
        return false;
    }
    // printf("Antes fn->accion\n");
    fn->accion(ctx);
    return true;
}

void menu_mostrar(Menu* m) {
    printf("Opciones: \n");
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
