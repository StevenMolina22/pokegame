#include "pa2m.h"
#include "../src/tda_juego.h"

void prueba_crear_juego() {
    pa2m_nuevo_grupo("Pruebas creacion juego");
    Juego* j = juego_crear();

    pa2m_afirmar(j != NULL, "Juego no es null");
    juego_destruir(j);
}

int main() {
    prueba_crear_juego();
}
