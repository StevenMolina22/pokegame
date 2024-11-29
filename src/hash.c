#include "hash.h"
#include "hash_utils.h"

#define FACTOR_REHASH 0.75

hash_t *hash_crear(size_t cap)
{
	hash_t *hash = malloc(sizeof(hash_t));
	if (!hash)
		return NULL;
	nodo_t **tabla = calloc(cap, sizeof(nodo_t *));
	if (!tabla) {
		free(hash);
		return NULL;
	}
	hash->tabla = tabla;
	hash->size = 0;
	hash->cap = cap;
	return hash;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;
	return hash->size;
}

bool hash_insertar(hash_t *hash, char *_clave, void *valor, void **encontrado)
{
	if (!hash || !_clave)
		return false;
	if ((float)hash->size / (float)hash->cap > FACTOR_REHASH) {
		if (!hash_rehash(hash))
			return false;
	}
	// encontrar nodo y actualizar argumento
	nodo_t *nodo = encontrar_nodo(hash, _clave);
	if (nodo) {
		if (encontrado)
			*encontrado = nodo->entrada->valor;
		nodo->entrada->valor = valor;
		return true;
	}
	if (encontrado)
		*encontrado = NULL;

	// crear clave y agregar
	char *clave = malloc(strlen(_clave) + 1);
	if (!clave)
		return false;
	strcpy(clave, _clave);
	if (!agregar_entrada(hash, clave, valor)) {
		free(clave);
		return false;
	}
	hash->size++;
	return true;
}

void *hash_buscar(hash_t *hash, char *clave)
{
	if (!hash || !clave)
		return NULL;
	nodo_t *nodo = encontrar_nodo(hash, clave);
	if (!nodo)
		return NULL;
	return nodo->entrada->valor;
}

bool hash_contiene(hash_t *hash, char *clave)
{
	if (!hash || !clave)
		return false;
	return encontrar_nodo(hash, clave) != NULL;
}

void *hash_quitar(hash_t *hash, char *clave)
{
	if (!hash || !clave)
		return NULL;
	size_t idx = hasher(clave) % hash->cap;
	nodo_t *nodo = encontrar_nodo(hash, clave);
	if (!nodo)
		return NULL;
	if (nodo->ant) { // no es el primero
		nodo->ant->sig = nodo->sig;
	} else { // es el primero
		hash->tabla[idx] = nodo->sig;
	}
	if (nodo->sig) { // si no es el ultimo
		nodo->sig->ant = nodo->ant;
	}
	void *valor = nodo->entrada->valor;
	nodo_destruir(nodo);
	hash->size--;
	return valor;
}

size_t hash_iterar(hash_t *hash, bool (*f)(char *, void *, void *), void *ctx)
{
	if (!hash || !f)
		return 0;
	size_t iterados = 0;
	for (size_t i = 0; i < hash->cap; i++) {
		nodo_t *actual = hash->tabla[i];
		while (actual) {
			iterados++;
			if (!f(actual->entrada->clave, actual->entrada->valor,
			       ctx)) {
				return iterados;
			}
			actual = actual->sig;
		}
	}
	return iterados;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;
	for (size_t i = 0; i < hash->cap; i++) {
		nodo_t *actual = hash->tabla[i];
		while (actual) {
			nodo_t *siguiente = actual->sig;
			if (destructor)
				destructor(actual->entrada->valor);
			nodo_destruir(actual);
			actual = siguiente;
		}
	}
	free(hash->tabla);
	free(hash);
}
