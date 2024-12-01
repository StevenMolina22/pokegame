#include "pa2m.h"
#include "../src/tipos.h"
#include "../src/tda_tablero.h"
#include "../src/tipo_jugador.h"
#include "../src/tipo_poke.h"
#include "../src/tda_pokedex.h"

void prueba_crear_tablero() {
    pa2m_nuevo_grupo("Pruebas creacion tablero");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    pa2m_afirmar(t != NULL, "Tablero no es null");
    pa2m_afirmar(tablero_ancho(t) == 32, "El ancho del tablero es correcto");
    pa2m_afirmar(tablero_alto(t) == 15, "El alto del tablero es correcto");

    tablero_destruir(t);
}

void prueba_destruir_tablero() {
    pa2m_nuevo_grupo("Pruebas destruccion tablero");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    tablero_destruir(t);
    pa2m_afirmar(true, "Tablero destruido correctamente");
}

void prueba_captura_pokemon() {
    pa2m_nuevo_grupo("Pruebas captura pokemon");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    Poke* p = poke_crear("Pikachu", 100, Amarillo, "patron");
    p->x = j->x;
    p->y = j->y;

    pa2m_afirmar(tablero_esta_capturado(t, p), "El jugador ha capturado el pokemon");

    poke_destruir(p);
    tablero_destruir(t);
}

void prueba_mostrar_tablero() {
    pa2m_nuevo_grupo("Pruebas mostrar tablero");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    tablero_mostrar(t);
    pa2m_afirmar(true, "Tablero mostrado correctamente");

    tablero_destruir(t);
}

int main() {
    prueba_crear_tablero();
    prueba_destruir_tablero();
    prueba_captura_pokemon();
    prueba_mostrar_tablero();

    return pa2m_mostrar_reporte();
}
