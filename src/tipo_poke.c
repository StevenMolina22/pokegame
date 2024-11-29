#include "tipo_poke.h"
#include "io_csv.h"
#include "io_utils.h"
#include "lista.h"

#define N_COLS 4

Poke* poke_crear(char* nombre, size_t puntos, Color color, char* patron) {
    Poke* poke = malloc(sizeof(Poke));
    if (poke == NULL) {
        return NULL;
    }
    poke->nombre = nombre;
    poke->color = color;
    poke->puntos = puntos;
    poke->patron = patron;
    poke->x = (size_t)rand() % (ANCHO);
    poke->y = (size_t)rand() % (ALTO);
    return poke;
}

void poke_inicial_color(Poke* p, char* dest) {
    switch (p->color) {
        case Azul:
            sprintf(dest, "%s%c", ANSI_COLOR_BLUE, p->nombre[0]);
            break;
        case Amarillo:
            sprintf(dest, "%s%c", ANSI_COLOR_BLUE, p->nombre[0]);
            break;
        case Magenta:
            sprintf(dest, "%s%c", ANSI_COLOR_MAGENTA, p->nombre[0]);
            break;
        case Verde:
            sprintf(dest, "%s%c", ANSI_COLOR_GREEN, p->nombre[0]);
            break;
        case Rojo:
            sprintf(dest, "%s%c", ANSI_COLOR_RED, p->nombre[0]);
            break;
        case Rosa:
            sprintf(dest, "%s%c", ANSI_COLOR_MAGENTA, p->nombre[0]);
            break;
    }
}

Poke *leer_pokemon(CSV *archivo)
{
	bool (*funciones[N_COLS])(const char *, void *) = {
		read_string, read_int, read_string, read_string
	};

	char* nombre = NULL;
	int puntos;
	char* color;
	char* patron;
	void* punteros[N_COLS] = { &nombre, &puntos, &color, &patron };

	// Lee una línea del CSV
	if (leer_linea_csv(archivo, N_COLS, funciones, punteros) != N_COLS) {
		free(nombre); // Libera en caso de fallo
		return NULL;
	}

	// Crea un nuevo Pokémon
	Poke *pokemon = malloc(sizeof(Poke));
	if (!pokemon) {
		free(nombre);
		return false;
	}

	*pokemon = (Poke) { .nombre = nombre, .puntos = (size_t)puntos, .patron = patron};

	// color
	if (strcmp(color, "AMARILLO")) {
	   pokemon->color = Amarillo;
	} else if (strcmp(color, "ROJO")) {
	   pokemon->color = Rojo;
	} else if (strcmp(color, "AZUL")) {
	   pokemon->color = Azul;
	} else if (strcmp(color, "MAGENTA")) {
	   pokemon->color = Magenta;
	} else if (strcmp(color, "VERDE")) {
	   pokemon->color = Verde;
	}
	return pokemon;
}

bool agregar_pokemones(CSV *archivo, Lista *pokedex)
{
	Poke *pokemon;
	// Lee cada Pokémon y lo agrega a la lista
	while ((pokemon = leer_pokemon(archivo)) != NULL) {
		if (!lista_agregar_final(pokedex, pokemon)) {
			poke_destruir(pokemon); // Libera si no se puede agregar
			return false;
		}
	}

	return true;
}

void poke_destruir(void* p) {
    free(p);
}
