#include "tda_pokedex.h"
#include "lista.h"
#include "tipo_poke.h"
#include "tipos.h"

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

void pokedex_agregar_random(Pokedex* pkx) {
    Pokedex* pkx_temp = pokedex_crear();
    if (pkx_temp == NULL) {
        return;
    }
    Poke* p1 = poke_crear("Pikachu", 15, Amarillo, "I");
    Poke* p2 = poke_crear("Charmander", 10, Rojo, "J");
    Poke* p3 = poke_crear("Lapras", 15, Azul, "NRORSRER");
    Poke* p4 = poke_crear("Mew", 27, Magenta, "R");
    Poke* p5 = poke_crear("Lotad", 5, Magenta, "R");
    Poke* p6 = poke_crear("Cacnea", 5, Rojo, "EEEROOOR");
    Poke* p7 = poke_crear("Pachirisu", 12, Verde, "NNNRSSSR");

    pokedex_agregar(pkx_temp, p1);
    pokedex_agregar(pkx_temp, p2);
    pokedex_agregar(pkx_temp, p3);
    pokedex_agregar(pkx_temp, p4);
    pokedex_agregar(pkx_temp, p5);
    pokedex_agregar(pkx_temp, p6);
    pokedex_agregar(pkx_temp, p7);

    int n = rand() % 7;
    printf("Random number: %d\n", n);
    Poke* elegido;
    lista_obtener(pkx_temp->lista, (size_t)n, (void**)&elegido);
    Poke* nuevo = poke_copiar(elegido);
    pokedex_agregar(pkx, nuevo);

    // limpiar temp
    pokedex_destruir(pkx_temp);
}

void pokedex_destruir(Pokedex* pkx) {
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
	Poke *p;
	while ((p = poke_leer(csv)) != NULL) {
		if (!lista_agregar(pkx->lista, p)) {
		poke_destruir(p); // Libera si no se puede agregar
			return false;
		}
	}
	return true;
}
