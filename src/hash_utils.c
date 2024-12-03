#include "hash.h"
#include "hash_utils.h"

// algoritmo de DJB2 (Daniel J. Bernstein)
size_t hasher(const char *str)
{
	size_t idx = 5381;
	size_t c;

	while ((c = (size_t)*str++)) {
		idx = ((idx << 5) + idx) + c; // hash * 33 + c
	}
	return idx;
}

Nodo *nodo_crear(char *clave, void *valor)
{
	Nodo *nodo = malloc(sizeof(Nodo));
	if (!nodo)
		return NULL;
	entrada_t *entrada = malloc(sizeof(entrada_t));
	if (!entrada) {
		free(nodo);
		return NULL;
	}
	entrada->clave = clave;
	entrada->valor = valor;
	nodo->entrada = entrada;
	nodo->sig = NULL;
	nodo->ant = NULL;
	return nodo;
}

void nodo_destruir(Nodo *nodo)
{
	free(nodo->entrada->clave);
	free(nodo->entrada);
	free(nodo);
}

Nodo *encontrar_nodo(Hash *hash, char *clave)
{
	size_t idx = hasher(clave) % hash->cap;
	Nodo *actual = hash->tabla[idx];
	while (actual) {
		if (strcmp(actual->entrada->clave, clave) == 0) {
			return actual;
		}
		actual = actual->sig;
	}
	return NULL;
}

bool agregar_entrada(Hash *hash, char *clave, void *valor)
{
	size_t idx = hasher(clave) % hash->cap;
	Nodo *nuevo = nodo_crear(clave, valor);
	if (!nuevo)
		return false;
	Nodo *nodo = hash->tabla[idx];
	if (nodo) {
		nuevo->sig = nodo;
		nodo->ant = nuevo;
	}
	hash->tabla[idx] = nuevo;
	return true;
}

bool hash_rehash(Hash *hash)
{
	hash->cap *= 2;
	Nodo **tabla_vieja = hash->tabla;
	Nodo **tabla = calloc(hash->cap, sizeof(Nodo *));
	if (!tabla)
		return false;
	hash->tabla = tabla;
	hash->size = 0;
	for (size_t i = 0; i < hash->cap / 2; i++) {
		Nodo *nodo = tabla_vieja[i];
		while (nodo) {
			Nodo *siguiente = nodo->sig;
			if (!agregar_entrada(hash, nodo->entrada->clave,
					     nodo->entrada->valor))
				return false;
			free(nodo->entrada);
			free(nodo);
			nodo = siguiente;
			hash->size++;
		}
	}
	free(tabla_vieja);
	return true;
}
