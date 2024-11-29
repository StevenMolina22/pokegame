#ifndef TDA_MENU_H
#define TDA_MENU_H

#include "tipos.h"

typedef struct menu Menu;

/**
 *
 */
Menu* menu_crear();

/**
 *
 */
bool menu_accion(Menu* m, char c);

/**
 *
 */
void menu_mostrar(Menu* m);

/**
 *
 */
void menu_destruir(Menu* m);

#endif
