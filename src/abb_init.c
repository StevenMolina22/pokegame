#include "abb.h"
#include "abb_privado.h"

static void nodo_destruir_todo(Nodo *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;
	nodo_destruir_todo(nodo->izq, destructor);
	nodo_destruir_todo(nodo->der, destructor);
	if (destructor)
		destructor(nodo->elemento);
	free(nodo);
}

abb_t *abb_crear(int (*comparador)(void *, void *))
{
	if (!comparador)
		return NULL;
	abb_t *abb = calloc(sizeof(abb_t), 1);
	if (!abb)
		return NULL;
	abb->comparador = comparador;
	return abb;
}

void abb_destruir(abb_t *abb)
{
	if (!abb)
		return;
	nodo_destruir_todo(abb->raiz, NULL);
	free(abb);
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
	if (!abb)
		return;
	nodo_destruir_todo(abb->raiz, destructor);
	free(abb);
}
