
#include <stdio.h>
#include "pa2m.h"
#include <stdlib.h>
#include <string.h>
#include "../src/tda_pokedex.h"
#include "../src/tipo_poke.h"
#include "../src/io_csv.h"

void test_pokedex_crear_destruir() {
    Pokedex* pkx = pokedex_crear();
    pa2m_afirmar(pkx != NULL, "Pkx no es null al crear");
    pokedex_destruir(pkx);
}

void test_pokedex_agregar_contar() {
    Pokedex* pkx = pokedex_crear();
    Poke* p1 = poke_crear("Pikachu", 100, Amarillo, "JJ");
    Poke* p2 = poke_crear("Charmander", 200, Rojo, "II");

    pokedex_agregar(pkx, p1);
    pokedex_agregar(pkx, p2);

    pa2m_afirmar(pokedex_len(pkx) == 2, "Cantidad es 2 al insertar");
    pokedex_destruir(pkx);
}

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

void test_pokedex_copiar() {
    Pokedex* pkx = pokedex_crear();
    Poke* p1 = poke_crear("Eevee", 180, Magenta, "Normal");

    pokedex_agregar(pkx, p1);

    Pokedex* pkx_copia = pokedex_copiar(pkx);
    pa2m_afirmar(pokedex_len(pkx_copia) == 1, "La cantidad es 1 luego de insertar");

    pokedex_destruir(pkx);
    pokedex_destruir(pkx_copia);
}

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


void test_pokedex_agregar_random() {
    Pokedex* pkx_original = pokedex_crear();
    Pokedex* pkx_destino = pokedex_crear();

    Poke* p1 = poke_crear("Mewtwo", 500, Magenta, "NSE");
    Poke* p2 = poke_crear("Gyarados", 400, Azul, "NSE");
    Poke* p3 = poke_crear("Charizard", 300, Rojo, "NSE");

    pokedex_agregar(pkx_original, p1);
    pokedex_agregar(pkx_original, p2);
    pokedex_agregar(pkx_original, p3);

    bool agregado = pokedex_agregar_random(pkx_original, pkx_destino);
    pa2m_afirmar(agregado == true, "Se agregó un pokemon aleatorio exitosamente");
    pa2m_afirmar(pokedex_len(pkx_destino) == 1, "La pokedex destino tiene un pokemon");

    pokedex_destruir(pkx_original);
    pokedex_destruir(pkx_destino);
}

void test_pokedex_lista() {
    Pokedex* pkx = pokedex_crear();
    Poke* p1 = poke_crear("Snorlax", 300, Verde, "Normal");
    Poke* p2 = poke_crear("Lapras", 400, Azul, "Agua/Hielo");

    pokedex_agregar(pkx, p1);
    pokedex_agregar(pkx, p2);

    Lista* lista_pokes = pokedex_lista(pkx);
    pa2m_afirmar(lista_pokes != NULL, "Se obtuvo una lista de pokemones");
    pa2m_afirmar(lista_len(lista_pokes) == 2, "La lista contiene dos pokemones");

    pokedex_destruir(pkx);
}

void test_pokedex_imprimir_nombres() {
    Pokedex* pkx = pokedex_crear();
    Poke* p1 = poke_crear("Zapdos", 500, Amarillo, "Eléctrico");
    Poke* p2 = poke_crear("Articuno", 500, Azul, "Hielo");

    pokedex_agregar(pkx, p1);
    pokedex_agregar(pkx, p2);

    printf("Prueba de impresión de nombres:\n");
    pokedex_print_nombres(pkx, stdout); // Salida esperada: Articuno, Zapdos (orden alfabético)

    pokedex_destruir(pkx);
}

void test_pokedex_copiar_independencia() {
    Pokedex* pkx_original = pokedex_crear();
    Pokedex* pkx_copia = pokedex_copiar(pkx_original);

    Poke* p1 = poke_crear("Dragonite", 600, Amarillo, "Dragón");
    pokedex_agregar(pkx_original, p1);

    pa2m_afirmar(pokedex_len(pkx_original) == 1, "Original tiene un pokemon");
    pa2m_afirmar(pokedex_len(pkx_copia) == 0, "Copia sigue vacía, es independiente");

    pokedex_destruir(pkx_original);
    pokedex_destruir(pkx_copia);
}

void test_pokedex_cargar_csv_inexistente() {
    Pokedex* pkx = pokedex_crear();
    CSV* csv = csv_abrir("inexistente.csv", ',');

    pa2m_afirmar(csv == NULL, "El archivo CSV inexistente no pudo abrirse");
    bool resultado = pokedex_cargar_desde(pkx, csv);
    pa2m_afirmar(resultado == false, "No se pudo cargar datos de un archivo inexistente");

    pokedex_destruir(pkx);
}

int main() {
    pa2m_nuevo_grupo("Pruebas de Pokedex");
    test_pokedex_crear_destruir();
    test_pokedex_agregar_contar();
    test_pokedex_vaciar();
    test_pokedex_copiar();
    test_pokedex_cargar_desde_csv();
    // nuevas
    test_pokedex_agregar_random();
    test_pokedex_lista();
    test_pokedex_imprimir_nombres();
    test_pokedex_copiar_independencia();
    test_pokedex_cargar_desde_csv();
    test_pokedex_cargar_csv_inexistente();
    return pa2m_mostrar_reporte();
}
