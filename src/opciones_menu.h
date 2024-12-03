#ifndef OPCIONES_MENU_H
#define OPCIONES_MENU_H

#include "tda_menu.h"
#include "io_csv.h"
#include "tda_juego.h"

#define TIEMPO_MAX 60 // 1 minuto max

typedef struct accion_ctx {
    CSV* csv;
    Juego* juego;
} AccionCtx;

int logica(int entrada, void* datos);

void init_menu(Menu* m);

bool opcion_mostrar_pokedex(void* ctx);

bool opcion_juego_jugar(void* ctx);

bool opcion_juego_jugar_semilla(void* ctx);

bool opcion_salir(void* ctx);
#endif
