#include "src/tda_menu.h"
#include "src/tda_juego.h"
#include "src/io_csv.h"

bool mostrar_pokedex(void* ctx);
bool juego_jugar(void* ctx);
bool juego_jugar_semilla(void* ctx);
bool salir(void* ctx);
//
void init_menu(Menu* m);

int logica(int entrada, void* datos) {
    Juego* juego = datos;
    borrar_pantalla();
    juego_correr(juego, entrada);
    esconder_cursor();
    return entrada == 'q' || entrada == 'Q';
}

typedef struct accion_ctx {
    CSV* archivo;
    Juego* juego;
} AccionCtx;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Uso: %s <archivo.csv>\n", argv[0]);
        return ERROR;
    }

    CSV* archivo = abrir_archivo_csv(argv[1], ',');
    if (archivo == NULL) {
        printf("Archivo inexistente\n");
        return ERROR;
    }

    Menu* m = menu_crear();
    init_menu(m);
    menu_mostrar(m);

    Juego* juego = juego_crear();
    AccionCtx ctx = {.juego = juego, .archivo = archivo};

    char id_opcion = (char)getchar();
    // char id_opcion = 'J';
    menu_accion(m, id_opcion, &ctx);

	return 0;
}

//o
void init_menu(Menu* m) {
    menu_agregar(m, 'P', "Pokedex", &mostrar_pokedex);
    menu_agregar(m, 'J', "Jugar", &juego_jugar);
    menu_agregar(m, 'S', "Semilla", &juego_jugar_semilla);
    menu_agregar(m, 'Q', "Quit", &salir);
}

bool mostrar_pokedex(void* ctx) {
    printf("Pokedex \n");

    return false;
}

bool juego_jugar(void* ctx) {
    printf("Adentro de jugar\n");
    AccionCtx* _ctx = ctx;
    Juego* juego = _ctx->juego;

    juego_iniciar(juego);
    game_loop(logica, juego);

    juego_mostrar_resultados(juego);
    mostrar_cursor();
	return true;
}

bool juego_jugar_semilla(void* ctx) {
    printf("Adentro de jugar semilla\n");
    AccionCtx* _ctx = ctx;
    Juego* juego = _ctx->juego;

    juego_iniciar(juego);
    game_loop(logica, juego);

    juego_mostrar_resultados(juego);
    mostrar_cursor();
    return false;
}

bool salir(void* ctx) {
    printf("Salir");
    return false;
}

// main
// -> loop
// -> logica
// -> juego_correr
