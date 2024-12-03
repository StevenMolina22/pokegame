#include "abb.h"
#include "abb_privado.h"

// ----- FUNCIONES AUXILIARES -----
Nodo *abb_nodo_crear(void *elemento)
{
	Nodo *nodo = calloc(sizeof(Nodo), 1);
	if (!nodo)
		return NULL;
	nodo->elemento = elemento;
	return nodo;
}

static Nodo *buscar_predecesor_inorden(Nodo *nodo)
{
	while (nodo->der)
		nodo = nodo->der;
	return nodo;
}

int sum_even(char *s)
{
	if (s[0] == '\0')
		return 0;
	return s[0] + sum_even(s + 2);
}

// ----- FIN FUNCIONES AUXILIARES
static Nodo *nodo_buscar(Nodo *nodo, void *elemento,
			   int (*comparador)(void *, void *), Nodo **padre)
{
	if (!nodo)
		return NULL;
	if (padre)
		*padre = nodo;
	if (!comparador)
		return NULL;

	int cmp = comparador(elemento, nodo->elemento);
	if (cmp == 0)
		return nodo;
	if (cmp < 0) {
		return nodo_buscar(nodo->izq, elemento, comparador, padre);
	} else {
		return nodo_buscar(nodo->der, elemento, comparador, padre);
	}
}
static Nodo *nodo_insertar(abb_t *abb, Nodo *nodo, void *elemento)
{
	if (!nodo) {
		Nodo *nuevo = abb_nodo_crear(elemento);
		if (nuevo)
			abb->nodos++;
		return nuevo;
	}

	if (!abb->comparador)
		return NULL;
	int cmp = abb->comparador(elemento, nodo->elemento);
	if (cmp > 0) {
		nodo->der = nodo_insertar(abb, nodo->der, elemento);
	} else {
		nodo->izq = nodo_insertar(abb, nodo->izq, elemento);
	}
	return nodo;
}

static Nodo *nodo_quitar_un_hijo(Nodo *nodo)
{
	// Funcion asume que nodo existe y tiene un solo hijo
	Nodo *temp = (nodo->izq) ? nodo->izq : nodo->der;
	free(nodo);
	return temp;
}

static Nodo *nodo_quitar(abb_t *abb, Nodo *nodo, void *buscado,
			   bool *fue_removido, void **encontrado)
{
	if (!nodo || !abb->comparador) {
		*fue_removido = false;
		return NULL;
	}
	int cmp = abb->comparador(buscado, nodo->elemento);
	if (cmp > 0) { // Buscar en subarbol derecho
		nodo->der = nodo_quitar(abb, nodo->der, buscado, fue_removido,
					encontrado);
	} else if (cmp < 0) { // Buscar en subarbol izquierdo
		nodo->izq = nodo_quitar(abb, nodo->izq, buscado, fue_removido,
					encontrado);
	} else { // Nodo encontrado
		if (encontrado)
			*encontrado = nodo->elemento;
		*fue_removido = true;

		if (!nodo->izq && !nodo->der) {
			free(nodo);
			return NULL;
		}

		if (!nodo->izq || !nodo->der)
			return nodo_quitar_un_hijo(nodo);

		// Caso: Nodo con dos hijos
		Nodo *max_nodo = buscar_predecesor_inorden(nodo->izq);
		void *temp = nodo->elemento;
		nodo->elemento = max_nodo->elemento;
		max_nodo->elemento = temp;
		nodo->izq = nodo_quitar(abb, nodo->izq, max_nodo->elemento,
					fue_removido, &max_nodo->elemento);
	}
	return nodo;
}

// ----- FUNCIONES DEL ABB -----
bool abb_insertar(abb_t *abb, void *elemento)
{
	if (!abb)
		return false;

	size_t nodos_iniciales = abb->nodos;
	abb->raiz = nodo_insertar(abb, abb->raiz, elemento);

	return abb->nodos > nodos_iniciales;
}

bool abb_quitar(abb_t *abb, void *buscado, void **encontrado)
{
	if (!abb) {
		return false;
	}
	bool removido = false;
	abb->raiz = nodo_quitar(abb, abb->raiz, buscado, &removido, encontrado);
	if (removido) {
		abb->nodos--;
	}
	return removido;
}

void *abb_obtener(abb_t *abb, void *elemento)
{
	if (!abb || !elemento)
		return NULL;
	Nodo *nodo = nodo_buscar(abb->raiz, elemento, abb->comparador, NULL);
	return nodo ? nodo->elemento : NULL;
}

size_t abb_cantidad(abb_t *abb)
{
	return abb ? abb->nodos : 0;
}
