#include "tda_tablero.h"
#include "lista/lista.h"
#include "tda_tablero_priv.h"
#include "tipo_poke.h"


// ---- INTERFAZ TDA
// INIT & DEINIT
Tablero* tablero_crear(size_t ancho, size_t alto, Jugador* jugador, Pokedex* pkx) {
    Tablero* t = calloc(1, sizeof(Tablero));
    if (t == NULL) {
        return NULL;
    }

    // TODO!: Verificar que la asignacion del string no rompa por temas de stack y stack frames
    for (size_t i = 0; i < ALTO; i++) {
        for (size_t j = 0; j < ANCHO; j++) {
            t->matriz[i][j] = malloc(20 * sizeof(char));
            strcpy(t->matriz[i][j], " ");
        }
    }

    t->jugador = jugador;
    t->pokes = pkx;
    t->ancho = ancho;
    t->alto = alto;
    return t;
}

void tablero_destruir(Tablero* t) {
    if (t == NULL) {
        return;
    }
    jugador_destruir(t->jugador);
    pokedex_destruir(t->pokes);
    for (size_t i = 0; i < t->alto; i++) {
        for (size_t j = 0; j < t->ancho; j++) {
            free(t->matriz[i][j]);
        }
    }
    free(t);
}

// ----GENERALES
void tablero_vaciar_celdas(Tablero* t) {
    if (t == NULL) {
        return;
    }
    for (size_t i = 0; i < ALTO; i++) {
        for (size_t j = 0; j < ANCHO; j++) {
            // t->matriz[i][j] = " ";
            strcpy(t->matriz[i][j], " ");
        }
    }
}

bool tablero_esta_capturado(Tablero* t, Poke* p) {
    if (t == NULL) {
        return false;
    }
    return t->jugador->x == p->x && t->jugador->y == p->y;
}

// IO

bool _print_nombre(void* s, void* file) {
    fprintf((FILE*)file, "%s ", (char*)s);
    return true;
}

void tablero_mostrar(Tablero* t) {
    if (t == NULL) {
        return;
    }
    tablero_vaciar_celdas(t);

    size_t x = t->jugador->x;
    size_t y = t->jugador->y;
    strcpy(t->matriz[y][x], ANSI_COLOR_MAGENTA ANSI_COLOR_BOLD "🧍"); // Jugador representado como "Ω"

    Poke* ultimo = t->jugador->ultimo_capturado;
    // Encabezado con estadísticas
    printf("%s╔══════════════════════════════════════════════════════════╗\n", ANSI_COLOR_WHITE ANSI_COLOR_BOLD);
    printf("%s║   %sEstadísticas: %-50s║\n", ANSI_COLOR_WHITE ANSI_COLOR_BOLD,
           ANSI_COLOR_GREEN,
           ANSI_COLOR_WHITE ANSI_COLOR_BOLD);
    printf("%s║   %sPuntos: %-47zu%s║\n",
           ANSI_COLOR_WHITE ANSI_COLOR_BOLD,
           ANSI_COLOR_GREEN, t->jugador->puntos,
           ANSI_COLOR_WHITE ANSI_COLOR_BOLD);
    printf("%s║   %sMultiplicador: %-40zu%s║\n",
           ANSI_COLOR_WHITE ANSI_COLOR_BOLD,
           ANSI_COLOR_YELLOW, t->jugador->multiplicador,
           ANSI_COLOR_WHITE ANSI_COLOR_BOLD);
    printf("%s║   %sNro de atrapados en combo: %-28zu%s║\n",
           ANSI_COLOR_WHITE ANSI_COLOR_BOLD,
           ANSI_COLOR_CYAN, t->jugador->cant_combo,
           ANSI_COLOR_WHITE ANSI_COLOR_BOLD);
    printf("%s║   %sUltimo Atrapado: %-38s%s║\n",
           ANSI_COLOR_WHITE ANSI_COLOR_BOLD,
           ANSI_COLOR_CYAN,
           ultimo ? t->jugador->ultimo_capturado->nombre : "",
           ANSI_COLOR_WHITE ANSI_COLOR_BOLD);
    printf("%s╚══════════════════════════════════════════════════════════╝\n", ANSI_COLOR_WHITE ANSI_COLOR_BOLD);

    // Actualiza la posición de los pokemones en el tablero
    ListaIt* it = lista_it_crear(pokedex_lista(t->pokes));
    while (lista_it_hay_siguiente(it)) {
        Poke* p = lista_it_actual(it);
        if (p != NULL) {
            poke_inicial_color(p, t->matriz[p->y][p->x]);
        }
        lista_it_avanzar(it);
    }
    lista_it_destruir(it);

    matriz_print(t->matriz);
}



// GETTERS
Jugador* tablero_jugador(Tablero* t) {
    if (t == NULL) {
        return NULL;
    }
    return t->jugador;
}

Pokedex* tablero_pokedex(Tablero* t) {
    if (t == NULL) {
        return NULL;
    }
    return t->pokes;
}

size_t tablero_ancho(Tablero* t) {
    if (t == NULL) {
        return 0;
    }
    return t->ancho;
}

size_t tablero_alto(Tablero* t) {
    if (t == NULL) {
        return 0;
    }
    return t->alto;
}



void matriz_print(str_t m[ALTO][ANCHO]) {
    // Línea superior
    printf("%s", ANSI_COLOR_WHITE ANSI_COLOR_BOLD "+");
    for (size_t j = 0; j < ANCHO; j++) {
        printf("%s-", ANSI_COLOR_WHITE ANSI_COLOR_BOLD "-");
    }
    printf("%s+\n", ANSI_COLOR_WHITE ANSI_COLOR_BOLD);

    for (size_t i = 0; i < ALTO; i++) {
        // Separador izquierdo
        printf("%s", ANSI_COLOR_WHITE ANSI_COLOR_BOLD "|");

        // Imprimir celdas de la fila
        for (size_t j = 0; j < ANCHO; j++) {
            printf("%s%s ", ANSI_COLOR_RESET, m[i][j]);
        }

        // Separador derecho
        printf("%s|\n", ANSI_COLOR_WHITE ANSI_COLOR_BOLD);
    }

    // Línea inferior
    printf("%s", ANSI_COLOR_WHITE ANSI_COLOR_BOLD "+");
    for (size_t j = 0; j < ANCHO; j++) {
        printf("%s-", ANSI_COLOR_WHITE ANSI_COLOR_BOLD "-");
    }
    printf("%s+\n", ANSI_COLOR_WHITE ANSI_COLOR_BOLD);
}
