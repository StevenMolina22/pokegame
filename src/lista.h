#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct lista Lista;
typedef struct lista_it ListaIt;

// NOTA IMPORTANTE: El nombre de algunas funciones y estructuras fue acortado para mayor legibilidad del codigo,
//              el funcionamiento de las funciones y sus firmas es exactamente el mismo

Lista *lista_crear();
void lista_destruir(Lista *);

/**
 * Destruye la lista aplicando la funcion destructora (si no es NULL) a cada elemento.
 * */
void lista_destruir_todo(Lista *, void (*destructor)(void *));

/*
 * Devuelve la cantidad de elementos de la lista.
 * Una lista NULL tiene 0 elementos.
 */
size_t lista_len(Lista *);

/**
 * Inserta un elemento en la lista en la posicion dada.
 *
 * Si la posición es mayor a la cantidad de elementos, es un error.
 *
 * Devuelve true si pudo, false en caso de error.
 *
 */
bool lista_insertar(Lista *l, size_t posicion, void *cosa);

/**
  * Inserta un elemento al final de la lista.
  */
bool lista_agregar(Lista *l, void *cosa);

/**
 * Elimina un elemento de la posicion dada.
 *
 * El elemento quitado se guarda en elemento_quitado (si se puede quitar y si no es null).
 *
 * En caso de error devuelve false, caso contrario true.
 */
bool lista_remover(Lista *l, size_t idx,
			   void **removido);

/**
 * Busca el elemento buscado en la lista y lo devuelve si lo encuentra.
 *
 * Para buscar el elemento, se aplica la función de comparacion.
 *
 * En caso de no encontrarlo devuelve NULL.
 */
void *lista_buscar(Lista *l, void *buscado,
			    int (*comparador)(void *, void *));

/**
 * Obtiene el elemento almacenado en una posición
 *
 * Si la posicion es inválida es un error.
 *
 * El elemento encontrado se almacena en elemento_encontrado (a menos que sea NULL);
 *
 * Devuelve true si pudo obtener el elemento o false en caso de error.
 */
bool lista_obtener(Lista *l, size_t posicion,
			    void **encontrado);

/**
 * Recorre la lista aplicando la funcion f a cada elemento en orden.
 *
 * ctx se le pasa como segundo parámetro a f.
 *
 * Si la funcion devuelve true se debe seguir iterando, caso contrario no.
 *
 * Devuelve la cantidad de elementos iterados.
 * */
size_t lista_iterar(Lista *l, bool (*f)(void *, void *),
			      void *ctx);

/**
 * Crea un iterador externo para una lista
 *
 * En caso de error devuelve NULL
 */
ListaIt *lista_it_crear(Lista *l);

/**
 * Devuelve true si hay siguiente.
 */
bool lista_it_hay_siguiente(ListaIt *);

/**
 *
 * Hace que el iterador avance al siguiente elemento de la lista.
 *
 */
void lista_it_avanzar(ListaIt *);

/**
 * Devuelve el elemento iterado
 */
void *lista_it_actual(ListaIt *);

/**
 * Eso
 */
void lista_it_destruir(ListaIt *);

#endif /* LISTA_H */
