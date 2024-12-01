#include "pa2m.h"
#include "../src/tda_menu.h"
#include <stdbool.h>
#include <stdio.h>

bool accion_prueba(void* ctx) {
    int* contador = (int*)ctx;
    (*contador)++;
    return true;
}

void prueba_crear_menu() {
    pa2m_nuevo_grupo("Pruebas creacion menu");
    Menu* m = menu_crear();

    pa2m_afirmar(m != NULL, "Menu no es null");

    menu_destruir(m);
}

void prueba_agregar_accion_menu() {
    pa2m_nuevo_grupo("Pruebas agregar accion al menu");
    Menu* m = menu_crear();

    pa2m_afirmar(menu_agregar(m, 'a', "Opcion A", accion_prueba), "Se agrega la accion 'a' correctamente");
    pa2m_afirmar(menu_agregar(m, 'b', "Opcion B", accion_prueba), "Se agrega la accion 'b' correctamente");

    menu_destruir(m);
}

void prueba_ejecutar_accion_menu() {
    pa2m_nuevo_grupo("Pruebas ejecutar accion del menu");
    Menu* m = menu_crear();
    int contador = 0;

    menu_agregar(m, 'a', "Opcion A", accion_prueba);
    menu_agregar(m, 'b', "Opcion B", accion_prueba);

    pa2m_afirmar(menu_accion(m, 'a', &contador), "Se ejecuta la accion 'a' correctamente");
    pa2m_afirmar(contador == 1, "El contador se incrementa correctamente");

    pa2m_afirmar(menu_accion(m, 'b', &contador), "Se ejecuta la accion 'b' correctamente");
    pa2m_afirmar(contador == 2, "El contador se incrementa correctamente");

    pa2m_afirmar(!menu_accion(m, 'c', &contador), "No se ejecuta la accion 'c' (no existe)");

    menu_destruir(m);
}

void prueba_mostrar_menu() {
    pa2m_nuevo_grupo("Pruebas mostrar menu");
    Menu* m = menu_crear();

    menu_agregar(m, 'a', "Opcion A", accion_prueba);
    menu_agregar(m, 'b', "Opcion B", accion_prueba);

    printf("Se espera ver las opciones 'a' y 'b':\n");
    menu_mostrar(m);

    menu_destruir(m);
}

void prueba_destruir_menu() {
    pa2m_nuevo_grupo("Pruebas destruir menu");
    Menu* m = menu_crear();

    menu_agregar(m, 'a', "Opcion A", accion_prueba);
    menu_agregar(m, 'b', "Opcion B", accion_prueba);

    menu_destruir(m);
    pa2m_afirmar(true, "Menu destruido correctamente");
}

int main() {
    prueba_crear_menu();
    prueba_agregar_accion_menu();
    prueba_ejecutar_accion_menu();
    prueba_mostrar_menu();
    prueba_destruir_menu();

    return pa2m_mostrar_reporte();
}
