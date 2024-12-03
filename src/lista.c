#include "lista.h"
#include <stdio.h>

typedef struct Nodo {
    void *data;
    struct Nodo *siguiente;
} Nodo;

struct lista {
    size_t cantidad;
    Nodo *frente;
    Nodo *fondo;
};

struct lista_iterador {
    Nodo *actual;
};

Lista *lista_crear() {
    Lista *lista = malloc(sizeof(Lista));
    if (!lista)
        return NULL;
    lista->cantidad = 0;
    lista->fondo = NULL;
    lista->frente = NULL;
    return lista;
}

void lista_destruir(Lista *lista) {
    if (!lista)
        return;
    Nodo *nodo = lista->frente;
    while (nodo != NULL) {
        Nodo *temp = nodo;
        nodo = nodo->siguiente;
        free(temp);
    }
    free(lista);
}

void lista_destruir_todo(Lista *lista, void (*destructor)(void *)) {
    if (!lista)
        return;
    Nodo *nodo = lista->frente;
    while (nodo != NULL) {
        if (destructor)
            destructor(nodo->data);
        Nodo *temp = nodo;
        nodo = nodo->siguiente;
        free(temp);
    }
    free(lista);
}

size_t lista_cantidad_elementos(Lista *lista) {
    if (!lista)
        return 0;
    return lista->cantidad;
}

bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa) {
    if (!lista || posicion > lista->cantidad)
        return false;
    Nodo *nuevo = malloc(sizeof(Nodo));
    if (!nuevo)
        return false;
    nuevo->data = cosa;
    nuevo->siguiente = NULL;

    if (posicion == 0) {
        nuevo->siguiente = lista->frente;
        lista->frente = nuevo;
        if (lista->cantidad == 0)
            lista->fondo = nuevo;
    } else {
        Nodo *nodo = lista->frente;
        for (size_t i = 0; i < posicion - 1; i++) {
            nodo = nodo->siguiente;
        }
        nuevo->siguiente = nodo->siguiente;
        nodo->siguiente = nuevo;
        if (posicion == lista->cantidad)
            lista->fondo = nuevo;
    }
    lista->cantidad++;
    return true;
}

bool lista_agregar_al_final(Lista *lista, void *cosa) {
    return lista_agregar_elemento(lista, lista->cantidad, cosa);
}

bool lista_quitar_elemento(Lista *lista, size_t posicion, void **elemento_quitado) {
    if (!lista || posicion >= lista->cantidad)
        return false;

    Nodo *nodo_a_quitar = lista->frente;
    if (posicion == 0) {
        lista->frente = nodo_a_quitar->siguiente;
        if (lista->cantidad == 1)
            lista->fondo = NULL;
    } else {
        Nodo *nodo_previo = lista->frente;
        for (size_t i = 0; i < posicion - 1; i++) {
            nodo_previo = nodo_previo->siguiente;
        }
        nodo_a_quitar = nodo_previo->siguiente;
        nodo_previo->siguiente = nodo_a_quitar->siguiente;
        if (posicion == lista->cantidad - 1)
            lista->fondo = nodo_previo;
    }
    if (elemento_quitado)
        *elemento_quitado = nodo_a_quitar->data;
    free(nodo_a_quitar);
    lista->cantidad--;
    return true;
}

void *lista_buscar_elemento(Lista *lista, void *buscado, int (*comparador)(void *, void *)) {
    if (!lista || !comparador)
        return NULL;
    Nodo *nodo = lista->frente;
    while (nodo != NULL) {
        if (comparador(buscado, nodo->data) == 0)
            return nodo->data;
        nodo = nodo->siguiente;
    }
    return NULL;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion, void **elemento_encontrado) {
    if (!lista || posicion >= lista->cantidad)
        return false;

    Nodo *nodo = lista->frente;
    for (size_t i = 0; i < posicion; i++) {
        nodo = nodo->siguiente;
    }

    if (elemento_encontrado)
        *elemento_encontrado = nodo->data;
    return true;
}

size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *), void *ctx) {
    if (!lista)
        return 0;

    Nodo *actual = lista->frente;
    size_t iterados = 0;
    while (actual != NULL) {
        if (!f(actual->data, ctx))
            break;
        actual = actual->siguiente;
        iterados++;
    }
    return iterados;
}

Lista_iterador *lista_iterador_crear(Lista *lista) {
    if (!lista)
        return NULL;

    Lista_iterador *iterador = malloc(sizeof(Lista_iterador));
    if (!iterador)
        return NULL;
    iterador->actual = lista->frente;
    return iterador;
}

bool lista_iterador_hay_siguiente(Lista_iterador *iterador) {
    return iterador && iterador->actual;
}

void lista_iterador_avanzar(Lista_iterador *iterador) {
    if (iterador && iterador->actual)
        iterador->actual = iterador->actual->siguiente;
}

void *lista_iterador_obtener_elemento_actual(Lista_iterador *iterador) {
    if (!iterador || !iterador->actual)
        return NULL;
    return iterador->actual->data;
}

void lista_iterador_destruir(Lista_iterador *iterador) {
    free(iterador);
}
