
#include "lista.h"
#include <stdio.h>

typedef struct Nodo {
	void *data;
	struct Nodo *siguiente;
} Node;

struct lista {
	size_t cantidad;
	Node *frente;
	Node *fondo;
};

struct lista_it {
	Node *actual;
};

Lista *lista_crear()
{
	Lista *lista = malloc(sizeof(Lista));
	if (!lista)
		return NULL;
	lista->cantidad = 0;
	lista->fondo = NULL;
	lista->frente = NULL;
	return lista;
}

void lista_destruir(Lista *lista)
{
	if (!lista)
		return;
	Node *nodo = lista->frente;
	while (nodo != NULL) {
		Node *temp = nodo;
		nodo = nodo->siguiente;
		free(temp);
	}
	free(lista);
}

void lista_destruir_todo(Lista *lista, void (*destructor)(void *))
{
	if (!lista)
		return;
	Node *nodo = lista->frente;
	while (nodo != NULL) {
		if (destructor)
			destructor(nodo->data);
		Node *temp = nodo;
		nodo = nodo->siguiente;
		free(temp);
	}
	free(lista);
}

size_t lista_len(Lista *lista)
{
	if (!lista)
		return 0;
	return lista->cantidad;
}

bool lista_insertar(Lista *lista, size_t idx, void *data)
{
	// Invalido
	if (!lista || idx > lista->cantidad)
		return false;
	Node *nuevo = malloc(sizeof(Node));
	if (!nuevo)
		return false;
	nuevo->data = data;
	nuevo->siguiente = NULL;

	if (idx == 0) {
		nuevo->siguiente = lista->frente;
		lista->frente = nuevo;
		if (lista->cantidad == 0)
			lista->fondo = nuevo;
	} else {
		Node *nodo = lista->frente;
		for (int i = 0; i < idx - 1; i++) {
			nodo = nodo->siguiente;
		}

		nuevo->siguiente = nodo->siguiente;
		nodo->siguiente = nuevo;
		if (idx == lista->cantidad)
			lista->fondo = nuevo;
	}
	lista->cantidad++;
	return true;
}

bool lista_agregar(Lista *lista, void *item)
{
	if (!lista)
		return false;
	Node *nuevo_nodo = malloc(sizeof(Node));
	if (!nuevo_nodo)
		return false;

	nuevo_nodo->data = item;
	nuevo_nodo->siguiente = NULL;
	if (!lista->frente)
		lista->frente = nuevo_nodo;

	if (lista->fondo)
		lista->fondo->siguiente = nuevo_nodo;
	lista->fondo = nuevo_nodo;

	lista->cantidad++;
	return true;
}

// Helper function for removal funcs
bool remover_nodo(Lista *lista, Node *nodo, void **removido)
{
	if (removido) {
		*removido = nodo->data;
	}
	free(nodo);
	lista->cantidad--;
	return true;
}

// ----- Funciones auxiliares para remover -----
// Funcion auxiliar
bool remover_frente(Lista *lista, void **removido)
{
	Node *nodo = lista->frente;
	lista->frente = nodo->siguiente;
	if (lista->cantidad == 1) {
		lista->fondo = NULL;
	}
	return remover_nodo(lista, nodo, removido);
}

// Funcion auxiliar
bool remover_fondo(Lista *lista, void **removido)
{
	Node *nodo = lista->fondo;
	Node *previo = lista->frente;
	while (previo->siguiente != nodo) {
		previo = previo->siguiente;
	}
	lista->fondo = previo;
	lista->fondo->siguiente = NULL;
	return remover_nodo(lista, nodo, removido);
}

// Funcion auxiliar
bool remover_mitad(Lista *lista, size_t idx, void **removido)
{
	Node *previo = lista->frente;
	for (size_t i = 0; i < idx - 1; i++) {
		previo = previo->siguiente;
	}
	Node *nodo = previo->siguiente;
	previo->siguiente = nodo->siguiente;
	if (idx == lista->cantidad - 1) {
		lista->fondo = previo;
	}
	return remover_nodo(lista, nodo, removido);
}

// Remover principal
bool lista_remover(Lista *lista, size_t idx, void **removido)
{
	if (!lista || idx >= lista->cantidad)
		return false;

	if (idx == 0) {
		return remover_frente(lista, removido);
	} else if (idx == lista->cantidad - 1) {
		return remover_fondo(lista, removido);
	} else {
		return remover_mitad(lista, idx, removido);
	}
}

void *lista_buscar(Lista *lista, void *buscado,
			    int (*cmp)(void *, void *))
{
	if (!lista || !cmp)
		return NULL;
	Node *nodo = lista->frente;
	while (nodo != NULL) {
		if (cmp(buscado, nodo->data) == 0)
			return nodo->data;
		nodo = nodo->siguiente;
	}
	return NULL;
}

bool lista_obtener(Lista *lista, size_t idx, void **encontrado)
{
	if (!lista || idx >= lista->cantidad)
		return false;

	Node *actual = lista->frente;
	for (size_t i = 0; i < idx; i++) {
		actual = actual->siguiente;
	}

	if (encontrado)
		*encontrado = actual->data;
	return true;
}

size_t lista_iterar(Lista *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (!lista)
		return 0;

	Node *actual = lista->frente;
	size_t i = 0;
	for (i = 0; actual != NULL; i++) {
		if (!f(actual->data, ctx))
			return ++i;
		actual = actual->siguiente;
	}
	return i;
}

ListaIt *lista_it_crear(Lista *lista)
{
	if (!lista)
		return NULL;

	ListaIt *iter = malloc(sizeof(ListaIt));
	iter->actual = lista->frente;
	return iter;
}

bool lista_it_hay_siguiente(ListaIt *iter)
{
	if (!iter || !iter->actual)
		return false;
	return true;
}

void lista_it_avanzar(ListaIt *iter)
{
	if (!iter || !iter->actual)
		return;
	iter->actual = iter->actual->siguiente;
}

void *lista_it_actual(ListaIt *iter)
{
	if (!iter || !iter->actual)
		return NULL;
	return iter->actual->data;
}

void lista_it_destruir(ListaIt *iter)
{
	free(iter);
}
