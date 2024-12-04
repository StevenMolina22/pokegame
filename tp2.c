#include "extra/engine.h"
#include "src/opciones_menu.h"
#include "src/tda_menu.h"
#include "src/tda_juego.h"
#include "src/io_csv.h"

void print_pokemon_ascii() {
    printf("  _____      _                             \n");
    printf(" |  __ \\    | |                            \n");
    printf(" | |__) |__ | | _____ _ __ ___   ___  _ __ \n");
    printf(" |  ___/ _ \\| |/ / _ \\ '_ ` _ \\ / _ \\| '_ \\ \n");
    printf(" | |  | (_) |   <  __/ | | | | | (_) | | | |\n");
    printf(" |_|   \\___/|_|\\_\\___|_| |_| |_|\\___/|_| |_|\n");
}

void bienvenida() {
    printf("%s", ANSI_COLOR_MAGENTA);
    print_pokemon_ascii();
    printf("%s", ANSI_COLOR_WHITE);
    printf("Bienvenido al juego de Pokemon, selecciona una opcion\n");
}

int main(int argc, char* argv[])
{
    // Args & CSV
    if (argc != 2) {
        printf("Uso: %s <archivo.csv>\n", argv[0]);
        return ERROR;
    }
    CSV* csv = csv_abrir(argv[1], ',');
    if (csv == NULL) {
        printf("Archivo inexistente\n");
        return ERROR;
    }

    bienvenida();

    // Menu
    Menu* m = menu_crear();
    if (m == NULL) {
        return ERROR;
    }
    init_menu(m);
    printf("%s", ANSI_COLOR_CYAN);
    menu_print(m);
    printf("%s", ANSI_COLOR_WHITE);

    // Juego
    Juego* juego = juego_crear();
    if (juego == NULL) {
        return ERROR;
    }
    AccionCtx ctx = {.juego = juego, .csv = csv};

    char id_opcion = (char)getchar();
    id_opcion = (char)toupper(id_opcion);
    menu_accion(m, id_opcion, &ctx);
    printf("%s", ANSI_COLOR_WHITE);


    // Cerrar
    mostrar_cursor();
    csv_cerrar(csv);
    juego_destruir(juego);
    menu_destruir(m);
	return 0;
}
