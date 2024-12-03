#include "abb.h"
#include "abb_privado.h"

static size_t nodo_vectorizar_inorden(Nodo *nodo, void **vector,
				      size_t tamaño, size_t *indice)
{
	if (!nodo || *indice >= tamaño)
		return 0;
	size_t contador = 0;
	contador += nodo_vectorizar_inorden(nodo->izq, vector, tamaño, indice);
	if (*indice < tamaño) {
		vector[*indice] = nodo->elemento;
		(*indice)++;
		contador++;
	}
	contador += nodo_vectorizar_inorden(nodo->der, vector, tamaño, indice);
	return contador;
}

static size_t nodo_vectorizar_preorden(Nodo *nodo, void **vector,
				       size_t tamaño, size_t *indice)
{
	if (!nodo || *indice >= tamaño)
		return 0;
	size_t contador = 0;
	if (*indice < tamaño) {
		vector[*indice] = nodo->elemento;
		(*indice)++;
		contador++;
	}
	contador += nodo_vectorizar_preorden(nodo->izq, vector, tamaño, indice);
	contador += nodo_vectorizar_preorden(nodo->der, vector, tamaño, indice);
	return contador;
}

static size_t nodo_vectorizar_postorden(Nodo *nodo, void **vector,
					size_t tamaño, size_t *indice)
{
	if (!nodo || *indice >= tamaño)
		return 0;
	size_t contador = 0;
	contador +=
		nodo_vectorizar_postorden(nodo->izq, vector, tamaño, indice);
	contador +=
		nodo_vectorizar_postorden(nodo->der, vector, tamaño, indice);
	if (*indice < tamaño) {
		vector[*indice] = nodo->elemento;
		(*indice)++;
		contador++;
	}
	return contador;
}

size_t abb_vectorizar_inorden(ABB *abb, void **vector, size_t tamaño)
{
	if (!abb || !vector)
		return 0;
	size_t indice = 0;
	return nodo_vectorizar_inorden(abb->raiz, vector, tamaño, &indice);
}

size_t abb_vectorizar_preorden(ABB *abb, void **vector, size_t tamaño)
{
	if (!abb || !vector)
		return 0;
	size_t indice = 0;
	return nodo_vectorizar_preorden(abb->raiz, vector, tamaño, &indice);
}

size_t abb_vectorizar_postorden(ABB *abb, void **vector, size_t tamaño)
{
	if (!abb || !vector)
		return 0;
	size_t indice = 0;
	return nodo_vectorizar_postorden(abb->raiz, vector, tamaño, &indice);
}
