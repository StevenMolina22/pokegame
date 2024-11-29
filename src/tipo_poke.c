#include "tipo_poke.h"

Poke* poke_crear(char* nombre, size_t puntos, Color color, char* patron) {
    Poke* poke = malloc(sizeof(Poke));
    if (poke == NULL) {
        return NULL;
    }
    poke->nombre = nombre;
    poke->color = color;
    poke->puntos = puntos;
    poke->patron = patron;
    poke->x = (size_t)rand() % (ANCHO + 1);
    poke->y = (size_t)rand() % (ALTO + 1);
    return poke;
}

void poke_destruir(void* p) {
}
