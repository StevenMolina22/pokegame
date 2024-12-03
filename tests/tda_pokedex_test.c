
#include <stdio.h>
#include "pa2m.h"
#include <stdlib.h>
#include <string.h>
#include "../src/tda_pokedex.h"
#include "../src/tipo_poke.h"
#include "../src/io/io_csv.h"

// Función auxiliar para crear un pokemon de prueba

// Prueba para la creación y destrucción de la Pokedex
void test_pokedex_crear_destruir() {
    Pokedex* pkx = pokedex_crear();
    pa2m_afirmar(pkx != NULL, "Pkx no es null al crear");
    pokedex_destruir(pkx);
}

// Prueba para agregar y contar pokemones en la Pokedex
void test_pokedex_agregar_contar() {
    Pokedex* pkx = pokedex_crear();
    Poke* p1 = poke_crear("Pikachu", 100, Amarillo, "JJ");
    Poke* p2 = poke_crear("Charmander", 200, Rojo, "II");

    pokedex_agregar(pkx, p1);
    pokedex_agregar(pkx, p2);

    pa2m_afirmar(pokedex_len(pkx) == 2, "Cantidad es 2 al insertar");
    pokedex_destruir(pkx);
}

// Prueba para vaciar la Pokedex
void test_pokedex_vaciar() {
    Pokedex* pkx = pokedex_crear();
    Poke* p1 = poke_crear("Bulbasaur", 150, Verde, "Grass");
    Poke* p2 = poke_crear("Squirtle", 120, Azul, "Water");

    pokedex_agregar(pkx, p1);
    pokedex_agregar(pkx, p2);

    pa2m_afirmar(pokedex_len(pkx) == 2, "Cantidad es 2 luego de insertar");

    pokedex_vaciar(pkx);
    pa2m_afirmar(pokedex_len(pkx) == 0, "Cantidad es 0 al vaciar");

    pokedex_destruir(pkx);
}

// Prueba para copiar la Pokedex
void test_pokedex_copiar() {
    Pokedex* pkx = pokedex_crear();
    Poke* p1 = poke_crear("Eevee", 180, Magenta, "Normal");

    pokedex_agregar(pkx, p1);

    Pokedex* pkx_copia = pokedex_copiar(pkx);
    pa2m_afirmar(pokedex_len(pkx_copia) == 1, "La cantidad es 1 luego de insertar");

    pokedex_destruir(pkx);
    pokedex_destruir(pkx_copia);
}

// Prueba para agregar un pokemon random a la Pokedex
// void test_pokedex_agregar_random() {
//     Pokedex* pkx = pokedex_crear();

//     pokedex_agregar_random(pkx);
//     pa2m_afirmar(pokedex_len(pkx) == 1, "Cantidad es 1 al agregar random");

//     pokedex_destruir(pkx);
// }

// Prueba para cargar pokemones desde un archivo CSV
//
void test_pokedex_cargar_desde_csv() {
    Pokedex* pkx = pokedex_crear();
    CSV* csv = csv_abrir("datos/pokedex.csv", ',');

    pa2m_afirmar(csv != NULL, "CSV no es null");
    bool resultado = pokedex_cargar_desde(pkx, csv);
    pa2m_afirmar(resultado == true, "se pudo cargar");
    pa2m_afirmar(pokedex_len(pkx) > 0, "Pokedex cargada tiene elementos");

    csv_cerrar(csv);
    pokedex_destruir(pkx);
}

int main() {
    pa2m_nuevo_grupo("Pruebas de Pokedex");
    test_pokedex_crear_destruir();
    test_pokedex_agregar_contar();
    // test_pokedex_agregar_random();
    test_pokedex_vaciar();
    test_pokedex_copiar();
    test_pokedex_cargar_desde_csv();

    return pa2m_mostrar_reporte();
}
