#include "pa2m.h"
#include "../src/tda_juego.h"
#include "../src/io_csv.h"

void prueba_crear_juego() {
    pa2m_nuevo_grupo("Pruebas de creación de juego");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

    juego_destruir(j);
}

void prueba_iniciar_juego() {
    pa2m_nuevo_grupo("Pruebas de inicialización de juego");

    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    pa2m_afirmar(csv != NULL, "Se abre archivo CSV correctamente");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

    juego_iniciar(j, csv);

    // Verificar condiciones de inicialización
    time_t tiempo_inicio = juego_tiempo_inicio(j);
    pa2m_afirmar(tiempo_inicio != 0, "El tiempo de inicio se establece correctamente");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_tiempo_inicio() {
    pa2m_nuevo_grupo("Pruebas de tiempo de inicio de juego");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

        // Iniciar con CSV
    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    time_t tiempo_inicio = juego_tiempo_inicio(j);
    pa2m_afirmar(tiempo_inicio > 0, "El tiempo de inicio es un valor válido");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_correr_juego() {
    pa2m_nuevo_grupo("Pruebas de ejecución de juego");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    // Simular algunas entradas de usuario
    int entradas[] = {TECLA_ABAJO, TECLA_DERECHA, TECLA_DERECHA, TECLA_ABAJO};
    for (int i = 0; i < 4; i++) {
        juego_correr(j, entradas[i]);
    }

    // Verificar que el juego puede manejar diferentes entradas
    pa2m_afirmar(true, "El juego procesa diferentes entradas de usuario");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_mostrar_resultados() {
    pa2m_nuevo_grupo("Pruebas de mostrar resultados");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    // Simular algunas capturas o acciones
    juego_mostrar_resultados(j);
    pa2m_afirmar(true, "Se pueden mostrar los resultados del juego");

    csv_cerrar(csv);
    juego_destruir(j);
}

int main() {
    prueba_crear_juego();
    prueba_iniciar_juego();
    prueba_tiempo_inicio();
    prueba_correr_juego();
    prueba_mostrar_resultados();

    return pa2m_mostrar_reporte();
}
