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

ABB *abb_crear(int (*comparador)(void *, void *))
{
	if (!comparador)
		return NULL;
	ABB *abb = calloc(sizeof(ABB), 1);
	if (!abb)
		return NULL;
	abb->comparador = comparador;
	return abb;
}

void abb_destruir(ABB *abb)
{
	if (!abb)
		return;
	nodo_destruir_todo(abb->raiz, NULL);
	free(abb);
}

void abb_destruir_todo(ABB *abb, void (*destructor)(void *))
{
	if (!abb)
		return;
	nodo_destruir_todo(abb->raiz, destructor);
	free(abb);
}
