#ifndef TIPOS_H
#define TIPOS_H
#include <stdlib.h>
#include <string.h>
#include "hash.h"

typedef struct entrada {
	char *clave;
	void *valor;
} entrada_t;

typedef struct nodo {
	entrada_t *entrada;
	struct nodo *sig;
	struct nodo *ant;
} Nodo;

struct hash {
	Nodo **tabla;
	size_t size;
	size_t cap;
};

size_t hasher(const char *str);
Nodo *nodo_crear(char *clave, void *valor);
void nodo_destruir(Nodo *nodo);
Nodo *encontrar_nodo(Hash *hash, char *clave);
bool agregar_entrada(Hash *hash, char *clave, void *valor);
bool hash_rehash(Hash *hash);
#endif
