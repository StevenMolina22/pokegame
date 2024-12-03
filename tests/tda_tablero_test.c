#include "pa2m.h"
#include "../src/tipos.h"
#include "../src/tda_tablero.h"
#include "../src/tipo_jugador.h"
#include "../src/tipo_poke.h"
#include "../src/tda_pokedex.h"

void prueba_crear_tablero() {
    pa2m_nuevo_grupo("Pruebas creación de tablero");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    pa2m_afirmar(t != NULL, "Se puede crear un tablero");
    pa2m_afirmar(tablero_ancho(t) == 32, "El ancho del tablero es correcto");
    pa2m_afirmar(tablero_alto(t) == 15, "El alto del tablero es correcto");

    tablero_destruir(t);
}

void prueba_destruir_tablero() {
    pa2m_nuevo_grupo("Pruebas destrucción de tablero");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    tablero_destruir(t);
    pa2m_afirmar(true, "Tablero destruido correctamente");
}

void prueba_tablero_mover_jugador() {
    pa2m_nuevo_grupo("Pruebas movimiento del jugador");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    tablero_mover_jugador(t, Derecha);
    pa2m_afirmar(j->x == 1 && j->y == 0, "El jugador se movió hacia la derecha");

    tablero_mover_jugador(t, Abajo);
    pa2m_afirmar(j->x == 1 && j->y == 1, "El jugador se movió hacia abajo");

    tablero_mover_jugador(t, Arriba);
    pa2m_afirmar(j->x == 1 && j->y == 0, "El jugador se movió hacia arriba");

    tablero_mover_jugador(t, Izquierda);
    pa2m_afirmar(j->x == 0 && j->y == 0, "El jugador se movió hacia la izquierda");

    tablero_destruir(t);
}

void prueba_tablero_mover_pokemon() {
    pa2m_nuevo_grupo("Pruebas movimiento de pokémon");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    Poke* p = poke_crear("Charmander", 50, Rojo, "NSE");
    p->x = 5;
    p->y = 5;
    pokedex_agregar(pkx, p);

    // posicion nueva esperada: x: 6 y: 5
    tablero_mover_pokes(t);
    pa2m_afirmar(p->y == 5, "El pokémon se movió hacia arriba y luego abajo (N)(S)");
    pa2m_afirmar(p->x == 6, "El pokémon se movió hacia la derecha (E)");

    tablero_destruir(t);
}

void prueba_tablero_captura_pokemon() {
    pa2m_nuevo_grupo("Pruebas captura de pokémon");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    Poke* p = poke_crear("Bulbasaur", 75, Verde, "R");
    p->x = j->x;
    p->y = j->y;
    pokedex_agregar(pkx, p);

    pa2m_afirmar(tablero_esta_capturado(t, p), "El pokémon fue capturado al estar en la misma posición que el jugador");

    tablero_destruir(t);
}

void prueba_tablero_mostrar() {
    pa2m_nuevo_grupo("Pruebas mostrar el tablero");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    tablero_mostrar(t);
    pa2m_afirmar(true, "El tablero fue mostrado correctamente");

    tablero_destruir(t);
}

void prueba_crear_tablero_borde() {
    pa2m_nuevo_grupo("Pruebas creación de tablero borde");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(0, 0, j, pkx);

    pa2m_afirmar(t == NULL, "No se puede crear un tablero con dimensiones inválidas");

    Tablero* t2 = tablero_crear(32, 15, NULL, pkx);
    pa2m_afirmar(t2 == NULL, "No se puede crear un tablero sin jugador");

    Tablero* t3 = tablero_crear(32, 15, j, NULL);
    pa2m_afirmar(t3 == NULL, "No se puede crear un tablero sin pokedex");

    tablero_destruir(t2);
    tablero_destruir(t3);
}

void prueba_destruir_tablero_borde() {
    pa2m_nuevo_grupo("Pruebas destrucción de tablero borde");
    Tablero* t = NULL;
    tablero_destruir(t);
    pa2m_afirmar(true, "Destruir un tablero NULL no genera errores");

    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t2 = tablero_crear(32, 15, j, pkx);
    tablero_destruir(t2);
    pa2m_afirmar(true, "Un tablero válido se destruye correctamente");
}

void prueba_tablero_mover_jugador_bordes() {
    pa2m_nuevo_grupo("Pruebas movimiento del jugador en bordes del tablero");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    tablero_mover_jugador(t, Izquierda);
    pa2m_afirmar(j->x == 0 && j->y == 0, "El jugador no se mueve fuera del límite izquierdo");

    tablero_mover_jugador(t, Arriba);
    pa2m_afirmar(j->x == 0 && j->y == 0, "El jugador no se mueve fuera del límite superior");

    for (int i = 0; i < 33; i++) tablero_mover_jugador(t, Derecha);
    pa2m_afirmar(j->x == 31 && j->y == 0, "El jugador no se mueve fuera del límite derecho");

    for (int i = 0; i < 16; i++) tablero_mover_jugador(t, Abajo);
    pa2m_afirmar(j->x == 31 && j->y == 14, "El jugador no se mueve fuera del límite inferior");

    tablero_destruir(t);
}

void prueba_tablero_mover_pokemon_borde() {
    pa2m_nuevo_grupo("Pruebas movimiento borde de pokémon");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    Poke* p1 = poke_crear("Eevee", 100, Amarillo, "NSEO");
    p1->x = 0;
    p1->y = 0;
    pokedex_agregar(pkx, p1);

    tablero_mover_pokes(t);
    pa2m_afirmar(p1->x == 0 && p1->y == 1, "El pokémon sigue el patrón NSEO y se mueve correctamente");

    Poke* p2 = poke_crear("Pikachu", 120, Amarillo, "RR");
    p2->x = 31;
    p2->y = 14;
    pokedex_agregar(pkx, p2);

    tablero_mover_pokes(t);
    pa2m_afirmar(p2->x <= 31 && p2->y <= 14, "El pokémon con movimiento aleatorio no supera los límites");

    tablero_destruir(t);
}

void prueba_tablero_captura_pokemon_extendida() {
    pa2m_nuevo_grupo("Pruebas borde de captura de pokémon");
    Pokedex* pkx = pokedex_crear();
    Jugador* j = jugador_crear();
    Tablero* t = tablero_crear(32, 15, j, pkx);

    Poke* p = poke_crear("Squirtle", 50, Azul, "N");
    p->x = j->x;
    p->y = j->y;
    pokedex_agregar(pkx, p);

    pa2m_afirmar(tablero_esta_capturado(t, p), "El pokémon es capturado al estar en la misma celda que el jugador");

    Poke* p2 = poke_crear("Charmander", 75, Rojo, "S");
    p2->x = 1;
    p2->y = 1;
    pokedex_agregar(pkx, p2);
    pa2m_afirmar(!tablero_esta_capturado(t, p2), "El pokémon no es capturado si no está en la misma celda");

    tablero_destruir(t);
}
int main() {
    prueba_crear_tablero();
    prueba_crear_tablero_borde();
    prueba_destruir_tablero();
    prueba_destruir_tablero_borde();
    prueba_tablero_mover_jugador();
    prueba_tablero_mover_jugador_bordes();
    prueba_tablero_mover_pokemon();
    prueba_tablero_mover_pokemon_borde();
    prueba_tablero_captura_pokemon();
    prueba_tablero_captura_pokemon_extendida();
    prueba_tablero_mostrar();
    return pa2m_mostrar_reporte();
}
