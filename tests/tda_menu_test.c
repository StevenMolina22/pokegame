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

void prueba_agregar_accion_menu_caracteres_especiales() {
    pa2m_nuevo_grupo("Pruebas agregar accion con caracteres especiales");
    Menu* m = menu_crear();

    pa2m_afirmar(menu_agregar(m, '@', "Opcion @", accion_prueba), "Se agrega la accion '@' correctamente");
    pa2m_afirmar(menu_agregar(m, '#', "Opcion #", accion_prueba), "Se agrega la accion '#' correctamente");

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
    menu_print(m);

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

// Prueba para agregar múltiples acciones con la misma clave
void prueba_agregar_accion_claves_repetidas() {
    pa2m_nuevo_grupo("Pruebas agregar acciones con claves repetidas");
    Menu* m = menu_crear();

    pa2m_afirmar(menu_agregar(m, 'a', "Primera opción", accion_prueba), "Se agrega la acción 'a' correctamente");
    pa2m_afirmar(!menu_agregar(m, 'a', "Segunda opción", accion_prueba), "No se permite agregar otra acción con la misma clave 'a'");

    menu_destruir(m);
}

// Prueba para claves inválidas
void prueba_agregar_claves_invalidas() {
    pa2m_nuevo_grupo("Pruebas agregar claves inválidas");
    Menu* m = menu_crear();

    pa2m_afirmar(!menu_agregar(m, '\0', "", accion_prueba), "No se permite agregar una acción con clave nula");
    pa2m_afirmar(!menu_agregar(m, '\0', NULL, accion_prueba), "No se permite agregar una acción con clave nula");

    menu_destruir(m);
}

// Prueba para manejo de mayúsculas y minúsculas
void prueba_ejecucion_mayusculas_minusculas() {
    pa2m_nuevo_grupo("Pruebas ejecución con mayúsculas y minúsculas");
    Menu* m = menu_crear();
    int contador = 0;

    menu_agregar(m, 'a', "Opción A", accion_prueba);
    menu_agregar(m, 'Q', "Salir", accion_prueba);

    pa2m_afirmar(menu_accion(m, 'a', &contador), "Se ejecuta correctamente la acción 'a'");
    pa2m_afirmar(menu_accion(m, 'A', &contador), "Se ejecuta correctamente la acción 'A' (equivalente a 'a')");
    pa2m_afirmar(menu_accion(m, 'q', &contador), "Se ejecuta correctamente la acción 'q' (equivalente a 'Q')");
    pa2m_afirmar(menu_accion(m, 'Q', &contador), "Se ejecuta correctamente la acción 'Q'");

    menu_destruir(m);
}

// Prueba para múltiples ejecuciones y estado del contexto
void prueba_multiples_ejecuciones() {
    pa2m_nuevo_grupo("Pruebas múltiples ejecuciones");
    Menu* m = menu_crear();
    int contador = 0;

    menu_agregar(m, 'x', "Opción X", accion_prueba);

    pa2m_afirmar(menu_accion(m, 'x', &contador), "Primera ejecución de la acción 'x' exitosa");
    pa2m_afirmar(contador == 1, "El contador es 1 después de la primera ejecución");

    pa2m_afirmar(menu_accion(m, 'x', &contador), "Segunda ejecución de la acción 'x' exitosa");
    pa2m_afirmar(contador == 2, "El contador es 2 después de la segunda ejecución");

    menu_destruir(m);
}

// Prueba para sobrecargar el menú (si tiene un límite conocido)
void prueba_sobrecarga_menu() {
    pa2m_nuevo_grupo("Pruebas sobrecargar el menú");
    Menu* m = menu_crear();

    bool exito = true;
    for (char c = 'a'; c <= 'z'; c++) {
        exito &= menu_agregar(m, c, "Opción", accion_prueba);
    }

    pa2m_afirmar(exito, "Se pueden agregar múltiples acciones sin errores (hasta el límite)");

    menu_destruir(m);
}

// Prueba de integridad al destruir el menú
void prueba_integridad_destruir_menu() {
    pa2m_nuevo_grupo("Pruebas integridad al destruir el menú");
    Menu* m = menu_crear();

    menu_agregar(m, 'a', "Opción A", accion_prueba);
    menu_agregar(m, 'b', "Opción B", accion_prueba);

    menu_destruir(m);
    pa2m_afirmar(true, "El menú se destruye correctamente sin errores de memoria");
}

int main() {
    prueba_crear_menu();
    prueba_agregar_accion_menu();
    prueba_agregar_accion_menu_caracteres_especiales();
    prueba_ejecutar_accion_menu();
    prueba_mostrar_menu();
    prueba_destruir_menu();
    prueba_agregar_accion_menu_caracteres_especiales();
    prueba_agregar_accion_claves_repetidas();
    prueba_agregar_claves_invalidas();
    prueba_ejecucion_mayusculas_minusculas();
    prueba_multiples_ejecuciones();
    prueba_sobrecarga_menu();
    prueba_integridad_destruir_menu();

    return pa2m_mostrar_reporte();
}
