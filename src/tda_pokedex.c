#include "tda_pokedex.h"
#include "abb/abb.h"
#include "lista/lista.h"
#include "tipo_poke.h"

struct pokedex {
    Lista* lista;
};

// Utils:
bool agregar_a_abb(void* poke, void* ctx);
void _poke_destruir(void* p);
bool _poke_print(void* poke, void* ctx);
bool _poke_print_nombre(void* poke, void* ctx);
int _cmp(void* p1, void* p2);

// ---- INIT & DEINIT
Pokedex* pokedex_crear() {
    Pokedex* pkx = malloc(sizeof(Pokedex));
    if (pkx == NULL) {
        return NULL;
    }
    Lista* l = lista_crear();
    if (l == NULL) {
        free(pkx);
        return NULL;
    }
    pkx->lista = l;
    return pkx;
}

void pokedex_destruir(Pokedex* pkx) {
    if (pkx == NULL) {
        return;
    }
    lista_destruir_todo(pkx->lista, &_poke_destruir);
    free(pkx);
}

Pokedex* pokedex_copiar(Pokedex* pkx) {
    if (pkx == NULL) {
        return NULL;
    }
    Pokedex* pkx_nueva = pokedex_crear();
    ListaIt* it = lista_it_crear(pkx->lista);
    while (lista_it_hay_siguiente(it)) {
        Poke* p = lista_it_actual(it);
        Poke* nuevo = poke_copiar(p);
        pokedex_agregar(pkx_nueva, nuevo);

        lista_it_avanzar(it);
    }
    lista_it_destruir(it);
    return pkx_nueva;
}

// ---- PRINCIPALES
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
    lista_destruir_todo(pkx->lista, &_poke_destruir);
    Lista* l = lista_crear();
    if (l == NULL) {
        return;
    }
    pkx->lista = l;
}

void pokedex_agregar_random(Pokedex* pkx_desde, Pokedex* pkx_hasta) {
    size_t idx = (size_t)rand() % pokedex_len(pkx_desde);
    Poke* p;
    lista_obtener(pokedex_lista(pkx_desde), idx, (void**)&p);
    pokedex_agregar(pkx_hasta, poke_copiar(p));
}

// ---- GETTERS
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


// ---- IO & CSV
void pokedex_print(Pokedex* pkx, FILE* archivo) {
    ABB* abb = abb_crear(&_cmp);
    lista_iterar(pkx->lista, &agregar_a_abb, abb);
    abb_iterar_inorden(abb, &_poke_print, NULL);
    abb_destruir(abb);
}

void pokedex_print_nombres(Pokedex* pkx, FILE* archivo) {
    ABB* abb = abb_crear(&_cmp);
    if (abb == NULL) {
        return;
    }
    lista_iterar(pkx->lista, &agregar_a_abb, abb);
    abb_iterar_inorden(abb, &_poke_print_nombre, archivo);
    abb_destruir(abb);
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


// UTILS WRAPPERS
bool agregar_a_abb(void* poke, void* ctx) {
    ABB* abb = ctx;
    abb_insertar(abb, poke);
    return true;
}

void _poke_destruir(void* p) {
    poke_destruir((Poke*)p);
}

bool _poke_print(void* poke, void* ctx) {
    poke_print((Poke*)poke, stdout);
    return true;
}

bool _poke_print_nombre(void* poke, void* ctx) {
    fprintf((FILE*)ctx, "%s\n", ((Poke*)poke)->nombre);
    return true;
}

int _cmp(void* p1, void* p2) {
    Poke* _p1 = p1;
    Poke* _p2 = p2;
    return strcmp(_p1->nombre, _p2->nombre);
}
