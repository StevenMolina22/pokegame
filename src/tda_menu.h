#ifndef TDA_MENU_H
#define TDA_MENU_H

#include "tipos.h"

typedef bool (*Fn)(void* ctx);

typedef struct {
    Fn accion;
} FuncAccion;

typedef struct menu Menu;

// ---- INIT & DEINIT

/**
 *
 */
Menu* menu_crear();
/**
 *
 */
void menu_destruir(Menu* m);



// ---- PRINCIPALES

/**
 *
 */
bool menu_accion(Menu* m, char c, void* ctx);
/**
 *
 */
bool menu_agregar(Menu* m, char id, char* opcion, Fn f_accion);

// ---- IO

/**
 *
 */
void menu_print(Menu* m);

#endif
