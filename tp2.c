#include "extra/engine.h"
#include "src/tda_menu.h"
#include "src/tda_juego.h"
#include "src/io/io_csv.h"
#include "src/tda_pokedex.h"

#define TIEMPO_MAX 60 // 1 minuto max

typedef struct accion_ctx {
    CSV* csv;
    Juego* juego;
} AccionCtx;

void init_menu(Menu* m);
bool mostrar_pokedex(void* ctx);
bool juego_jugar(void* ctx);
bool juego_jugar_semilla(void* ctx);
bool salir(void* ctx);

int logica(int entrada, void* datos) {
    Juego* juego = datos;
    borrar_pantalla();
    juego_correr(juego, entrada);
    esconder_cursor();
    bool tiempo_limite = (difftime(time(NULL), juego_tiempo_inicio(juego)) >= TIEMPO_MAX);
    return entrada == 'q' || entrada == 'Q' || tiempo_limite;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Uso: %s <archivo.csv>\n", argv[0]);
        return ERROR;
    }
    CSV* csv = csv_abrir(argv[1], ',');
    if (csv == NULL) {
        printf("Archivo inexistente\n");
        return ERROR;
    }

    Menu* m = menu_crear();
    if (m == NULL) {
        return ERROR;
    }
    init_menu(m);
    menu_mostrar(m);

    Juego* juego = juego_crear();
    if (juego == NULL) {
        return ERROR;
    }
    AccionCtx ctx = {.juego = juego, .csv = csv};

    char id_opcion = (char)getchar();
    id_opcion = (char)toupper(id_opcion);
    // char id_opcion = 'J';
    menu_accion(m, id_opcion, &ctx);

    mostrar_cursor();

    csv_cerrar(csv);
    juego_destruir(juego);
    menu_destruir(m);
	return 0;
}

void init_menu(Menu* m) {
    menu_agregar(m, 'P', "Pokedex", &mostrar_pokedex);
    menu_agregar(m, 'J', "Jugar", &juego_jugar);
    menu_agregar(m, 'S', "Semilla", &juego_jugar_semilla);
    menu_agregar(m, 'Q', "Quit", &salir);
}

bool mostrar_pokedex(void* ctx) {
    AccionCtx* _ctx = ctx;
    CSV* csv = _ctx->csv;

    Pokedex* pkx = pokedex_crear();
    pokedex_cargar_desde(pkx, csv);

    pokedex_print(pkx, stdout);
    pokedex_destruir(pkx);
    return false;
}

bool juego_jugar(void* ctx) {
    srand((unsigned int)time(NULL));
    AccionCtx* _ctx = ctx;
    Juego* juego = _ctx->juego;
    CSV* csv = _ctx->csv;

    juego_iniciar(juego, csv);
    game_loop(logica, juego);

    juego_mostrar_resultados(juego);
	return true;
}

bool juego_jugar_semilla(void* ctx) {
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

bool salir(void* ctx) {
    printf("Salir");
    return false;
}
