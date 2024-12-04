#include "opciones_menu.h"

// ---- OPCIONES AGREGADAS AL MENU
void init_menu(Menu* m) {
    menu_agregar(m, 'P', "Mostrar Pokedex", &opcion_mostrar_pokedex);
    menu_agregar(m, 'J', "Jugar", &opcion_juego_jugar);
    menu_agregar(m, 'S', "Jugar con Semilla", &opcion_juego_jugar_semilla);
    menu_agregar(m, 'Q', "Salir", &opcion_salir);
}

bool opcion_mostrar_pokedex(void* ctx) {
    AccionCtx* _ctx = ctx;
    CSV* csv = _ctx->csv;

    Pokedex* pkx = pokedex_crear();
    pokedex_cargar_desde(pkx, csv);

    pokedex_print(pkx, stdout);
    pokedex_destruir(pkx);
    return false;
}

bool opcion_juego_jugar(void* ctx) {
    srand((unsigned int)time(NULL));
    AccionCtx* _ctx = ctx;
    Juego* juego = _ctx->juego;
    CSV* csv = _ctx->csv;

    juego_iniciar(juego, csv);
    game_loop(logica, juego);

    juego_mostrar_resultados(juego);
	return true;
}

bool opcion_juego_jugar_semilla(void* ctx) {
    size_t semilla;
    printf("Ingrese una semilla: ");
    if (scanf("%zu", &semilla) == -1) {
        return false;
    };

    srand((unsigned int)semilla);
    AccionCtx* _ctx = ctx;
    Juego* juego = _ctx->juego;
    CSV* csv = _ctx->csv;

    juego_iniciar(juego, csv);
    game_loop(logica, juego);

    juego_mostrar_resultados(juego);
    return false;
}

bool opcion_salir(void* ctx) {
    printf("Saliendo...\n");
    return true;
}


// ---- LOGICA
int logica(int entrada, void* datos) {
    Juego* juego = datos;
    borrar_pantalla();
    juego_correr(juego, entrada);
    esconder_cursor();
    bool tiempo_limite = (difftime(time(NULL), juego_tiempo_inicio(juego)) >= TIEMPO_MAX);
    return entrada == 'q' || entrada == 'Q' || tiempo_limite;
}
