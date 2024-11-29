
#include "pa2m.h"
#include "src/tda_pokedex.h"  // Incluye las definiciones de la Pokedex y funciones asociadas

void probar_creacion_pokedex() {
    pa2m_nuevo_grupo("Pruebas de creación de la Pokedex");
    Pokedex *pokedex = pokedex_crear();

    pa2m_afirmar(pokedex != NULL, "Se creó la Pokedex correctamente");
    pa2m_afirmar(pokedex_len(pokedex) == 0, "La Pokedex recién creada está vacía");

    pokedex_destuir(pokedex);
    pa2m_afirmar(1, "La Pokedex se destruyó correctamente");
}

void probar_agregar_pokemones() {
    pa2m_nuevo_grupo("Pruebas de agregar pokemones a la Pokedex");

    Pokedex *pokedex = pokedex_crear();
    Poke poke1 = {"Pikachu", 10};
    Poke poke2 = {"Charmander",  15};

    pokedex_agregar(pokedex, &poke1);
    pa2m_afirmar(pokedex_len(pokedex) == 1, "Se agregó un pokemon a la Pokedex");

    pokedex_agregar(pokedex, &poke2);
    pa2m_afirmar(pokedex_len(pokedex) == 2, "Se agregaron dos pokemones a la Pokedex");

    Lista *pokemones = pokedex_lista(pokedex);
    pa2m_afirmar(lista_len(pokemones) == 2, "La lista interna contiene 2 pokemones");

    pokedex_destuir(pokedex);
}

void probar_remover_pokemones() {
    pa2m_nuevo_grupo("Pruebas de remover pokemones de la Pokedex");

    Pokedex *pokedex = pokedex_crear();
    Poke poke1 = {"Pikachu", 10};
    Poke poke2 = {"Charmander", 15};

    pokedex_agregar(pokedex, &poke1);
    pokedex_agregar(pokedex, &poke2);

    pokedex_remover(pokedex, 0);
    pa2m_afirmar(pokedex_len(pokedex) == 1, "Se eliminó un pokemon de la Pokedex");

    pokedex_remover(pokedex, 0);
    pa2m_afirmar(pokedex_len(pokedex) == 0, "Se eliminó el último pokemon de la Pokedex");

    pokedex_destuir(pokedex);
}

void probar_cargar_desde_archivo() {
    pa2m_nuevo_grupo("Pruebas de carga desde archivo");

    Pokedex *pokedex = pokedex_crear();

    pokedex_carga_desde(pokedex, "pokedex.txt");
    pa2m_afirmar(pokedex_len(pokedex) > 0, "Se cargaron pokemones desde el archivo");

    pokedex_destuir(pokedex);
}

void probar_spawn_y_random() {
    pa2m_nuevo_grupo("Pruebas de generación de pokemones");

    Pokedex *pokedex = pokedex_crear();

    pokedex_spawn(pokedex);
    pa2m_afirmar(pokedex_len(pokedex) > 0, "Se generaron pokemones automáticamente");

    pokedex_agregar_random(pokedex);
    pa2m_afirmar(pokedex_len(pokedex) > 0, "Se agregó un pokemon random a la Pokedex");

    pokedex_destuir(pokedex);
}

int main() {
    pa2m_nuevo_grupo("============== Pruebas de la Pokedex ===============");

    // probar_creacion_pokedex();
    // probar_agregar_pokemones();
    // probar_remover_pokemones();
    // probar_cargar_desde_archivo();
    // probar_spawn_y_random();

    return pa2m_mostrar_reporte();
}
