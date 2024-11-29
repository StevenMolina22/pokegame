#include "extra/engine.h"
#include "extra/ansi.h"
#include "src/tipo_jugador.h"
#include "src/tda_juego.h"

size_t max(size_t a, size_t b)
{
	return a > b ? a : b;
}

size_t min(size_t a, size_t b)
{
	return a < b ? a : b;
}

int logica(int entrada, void *datos)
{
	struct jugador *jugador = datos;
	borrar_pantalla();

	if (entrada == TECLA_DERECHA)
		jugador->x++;
	else if (entrada == TECLA_IZQUIERDA)
		jugador->x--;
	else if (entrada == TECLA_ARRIBA)
		jugador->y--;
	else if (entrada == TECLA_ABAJO)
		jugador->y++;

	jugador->x = min(20, max(0, jugador->x));
	jugador->y = min(10, max(0, jugador->y));

	jugador->iteraciones++;

	printf("Utilizar " ANSI_COLOR_CYAN ANSI_COLOR_BOLD "⬆⬇⬅➡" ANSI_COLOR_RESET " para moverse\n");

	printf("Presionar " ANSI_COLOR_RED ANSI_COLOR_BOLD "Q" ANSI_COLOR_RESET " para salir\n");

	printf("Iteraciones: %zu Tiempo: %zu\n", jugador->iteraciones, jugador->iteraciones / 5);

	for (size_t i = 0; i < jugador->y; i++) {
    	printf("\n");
	}

	for (size_t i = 0; i < jugador->x; i++) {
    	printf(" ");
	}

	printf(ANSI_COLOR_MAGENTA ANSI_COLOR_BOLD "Ω" ANSI_COLOR_RESET);

	printf("\n");
	esconder_cursor();

	return entrada == 'q' || entrada == 'Q'; // retorna 1 para salir o 0 para seguir
}

int logica2(int entrada, void* datos) {
    Juego* juego = datos;
    borrar_pantalla();
    // entrada = TECLA_DERECHA;
    juego_correr(juego, entrada);
    esconder_cursor();
    return entrada == 'q' || entrada == 'Q';
}

int logica3(int entrada, void *datos)
{
    Juego* juego = datos;
	Jugador *jugador = juego_jugador(juego);
	borrar_pantalla();

	if (entrada == TECLA_DERECHA)
		jugador->x++;
	else if (entrada == TECLA_IZQUIERDA)
		jugador->x--;
	else if (entrada == TECLA_ARRIBA)
		jugador->y--;
	else if (entrada == TECLA_ABAJO)
		jugador->y++;

	jugador->x = min(20, max(0, jugador->x));
	jugador->y = min(10, max(0, jugador->y));

	jugador->iteraciones++;

	printf("Utilizar " ANSI_COLOR_CYAN ANSI_COLOR_BOLD "⬆⬇⬅➡" ANSI_COLOR_RESET " para moverse\n");

	printf("Presionar " ANSI_COLOR_RED ANSI_COLOR_BOLD "Q" ANSI_COLOR_RESET " para salir\n");

	printf("Iteraciones: %zu Tiempo: %zu\n", jugador->iteraciones, jugador->iteraciones / 5);

	for (size_t i = 0; i < jugador->y; i++) {
    	printf("\n");
	}

	for (size_t i = 0; i < jugador->x; i++) {
    	printf(" ");
	}

	printf(ANSI_COLOR_MAGENTA ANSI_COLOR_BOLD "Ω" ANSI_COLOR_RESET);

	printf("\n");
	esconder_cursor();

	return entrada == 'q' || entrada == 'Q'; // retorna 1 para salir o 0 para seguir
}

int main()
{
    Juego* juego = juego_crear();
    juego_iniciar(juego);

	// struct jugador jugador = { 0 };

	// game_loop(logica, juego);
	game_loop(logica2, juego);
	// game_loop(logica3, juego);
	juego_mostrar_resultados(juego);

	mostrar_cursor();
	return 0;
}

// main
// -> loop
// -> logica
// -> juego_correr
