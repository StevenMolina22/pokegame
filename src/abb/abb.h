#ifndef ABB_H_
#define ABB_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct abb ABB;

/**
 * Crea un ABB con un comparador.
 */
ABB *abb_crear(int (*comparador)(void *, void *));

/**
 * Destruye el abb.
 */
void abb_destruir(ABB *abb);

/**
 * Destruye el abb aplicando el destructor a los elementos del usuario.
 */
void abb_destruir_todo(ABB *abb, void (*destructor)(void *));

/**
 * Inserta el elemento. Devuelve true si pudo o false si no pudo.
 */
bool abb_insertar(ABB *abb, void *elemento);

/**
 * Quita el elemento buscado del arbol. Si lo encuentra y encontrado no es NULL,
 * almacena el puntero.
 *
 * Devuelve true si pudo quitar el elemento.
 */
bool abb_quitar(ABB *abb, void *buscado, void **encontrado);

/**
 * Busca un elemento en el abb. Si lo encuentra lo devuelve. Caso contrario
 * devuelve NULL.
 */
void *abb_obtener(ABB *abb, void *elemento);

/**
 * Devuelve la cantidad de elementos en el abb.
 */
size_t abb_cantidad(ABB *abb);

/**
 * Recorre los elementos del abb en el orden específico y aplica la función f a
 * cada uno.
 *
 * Si la función f devuelve false, se deja de iterar.
 *
 * Devuelve la cantidad de veces que fue invocada la función f.
 */
size_t abb_iterar_inorden(ABB *abb, bool (*f)(void *, void *), void *ctx);
size_t abb_iterar_preorden(ABB *abb, bool (*f)(void *, void *), void *ctx);
size_t abb_iterar_postorden(ABB *abb, bool (*f)(void *, void *), void *ctx);

/**
 * Rellena el vector de punteros con los elementos del abb siguiendo un orden
 * dado. Tamaño indica la capacidad del vector.
 *
 * Devuelve la cantidad de elementos guardados en el vector.
 */
size_t abb_vectorizar_inorden(ABB *abb, void **vector, size_t tamaño);
size_t abb_vectorizar_preorden(ABB *abb, void **vector, size_t tamaño);
size_t abb_vectorizar_postorden(ABB *abb, void **vector, size_t tamaño);

#endif // ABB_H_
