#include "tda_pokedex.h"
#include "lista.h"
#include "tipo_poke.h"

struct pokedex {
    Lista* lista;
};

Pokedex* pokedex_crear() {
    Pokedex* pkx = malloc(sizeof(Pokedex));
    Lista* l = lista_crear();
    if (l == NULL) {
        free(pkx);
        return NULL;
    }
    pkx->lista = l;
    return pkx;
}

// TODO!: Es pokedex remover necesario?
void pokedex_remover(Pokedex* pkx, size_t idx) {}

void pokedex_agregar(Pokedex* pkx, Poke* p) {
    if (pkx == NULL) {
        return;
    }
    lista_agregar(pkx->lista, p);
}

void pokedex_vaciar(Pokedex* pkx) {
    if (pkx == NULL) {
        return;
    }
    lista_destruir_todo(pkx->lista, &poke_destruir);
    Lista* l = lista_crear();
    if (l == NULL) {
        return;
    }
    pkx->lista = l;
}

size_t pokedex_len(Pokedex* pkx) {
    if (pkx == NULL) {
        return 0;
    }
    return lista_len(pkx->lista);
}

Lista* pokedex_lista(Pokedex* pkx) {
    if (pkx == NULL) {
        return NULL;
    }
    return pkx->lista;
}

void pokedex_spawn(Pokedex* pkx) {
    Poke* p1 = poke_crear("Pikachu", 15, Amarillo, "I");
    Poke* p2 = poke_crear("Pikachu", 15, Amarillo, "J");
    Poke* p3 = poke_crear("Lapras", 15, Azul, "NRORSRER");
    pokedex_agregar(pkx, p1);
    pokedex_agregar(pkx, p2);
    pokedex_agregar(pkx, p3);
}

void pokedex_agregar_random(Pokedex* pkx) {
}

void pokedex_destuir(Pokedex* pkx) {
    if (pkx == NULL) {
        return;
    }
    lista_destruir_todo(pkx->lista, &poke_destruir);
}

// ---- IO & CSV
void pokedex_print(Pokedex* pkx, FILE* archivo) {
    ListaIt* it = lista_it_crear(pkx->lista);
    while (lista_it_hay_siguiente(it)) {
        Poke* p = lista_it_actual(it);
        poke_print(p, archivo);
        lista_it_avanzar(it);
    }
    fprintf(archivo, "\n");
    lista_it_destruir(it);
}

bool pokedex_cargar_desde(Pokedex *pkx, CSV *csv) {
	Poke *pokemon;
	while ((pokemon = poke_leer(csv)) != NULL) {
		if (!lista_agregar(pkx->lista, pokemon)) {
			poke_destruir(pokemon); // Libera si no se puede agregar
			return false;
		}
	}
	return true;
}
