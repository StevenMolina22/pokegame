#ifndef TDA_MENU_H
#define TDA_MENU_H

#include "tipos.h"

typedef bool (*Fn)(void* ctx);

typedef struct {
    Fn accion;
} FuncAccion;

typedef struct menu Menu;

/**
 *
 */
Menu* menu_crear();

/**
 *
 */
bool menu_accion(Menu* m, char c, void* ctx);

/**
 *
 */
bool menu_agregar(Menu* m, char id, char* opcion, Fn f_accion);

/**
 *
 */
void menu_mostrar(Menu* m);

/**
 *
 */
void menu_destruir(Menu* m);

#endif
