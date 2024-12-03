#include "lista.h"
#include "tda_tablero.h"
#include "tda_tablero_priv.h"

// ---- INTERFAZ TDA
void tablero_mover_jugador(Tablero *t, Direccion d)
{
	if (t == NULL) {
		return;
	}
	if (entrada_es_valida(t, d)) {
		mover_entidad(&t->jugador->x, &t->jugador->y, d);
	}
	t->jugador->ultimo_movimiento = d;
}

void tablero_mover_pokes(Tablero *t)
{
	if (t == NULL) {
		return;
	}
	Lista_iterador *it = lista_iterador_crear(pokedex_lista(t->pokes));
	while (lista_iterador_hay_siguiente(it)) {
		Poke *p = lista_iterador_obtener_elemento_actual(it);
		for (size_t i = 0; i < strlen(p->patron); i++) {
			if (es_patron_valido(t, p, p->patron[i])) {
				tablero_mover_poke(t, p, p->patron[i]);
			}
		}
		lista_iterador_avanzar(it);
	}
	lista_iterador_destruir(it);
}

// ---- AUXILIARES
void tablero_mover_poke(Tablero *t, Poke *p, Patron patron)
{
	switch (patron) {
	case PatronArriba:
		mover_entidad(&p->x, &p->y, patron_a_direccion(patron));
		break;
	case PatronAbajo:
		mover_entidad(&p->x, &p->y, patron_a_direccion(patron));
		break;
	case PatronDerecha:
		mover_entidad(&p->x, &p->y, patron_a_direccion(patron));
		break;
	case PatronIzquierda:
		mover_entidad(&p->x, &p->y, patron_a_direccion(patron));
		break;
	case PatronEspejo:
		mover_entidad(&p->x, &p->y, t->jugador->ultimo_movimiento);
		break;
	case PatronInverso:
		mover_entidad(&p->x, &p->y,
			      direccion_inversa(t->jugador->ultimo_movimiento));
		break;
	case PatronRandom:
		mover_random(t, p);
		break;
	}
}

void mover_entidad(size_t *x, size_t *y, Direccion d)
{
	switch (d) {
	case Arriba:
		(*y)--;
		break;
	case Abajo:
		(*y)++;
		break;
	case Derecha:
		(*x)++;
		break;
	case Izquierda:
		(*x)--;
		break;
	}
}

bool entrada_es_valida(Tablero *t, Direccion d)
{
	return esta_en_rango(t, t->jugador->x, t->jugador->y, d);
}

bool es_patron_valido(Tablero *t, Poke *p, Patron patron)
{
	switch (patron) {
	case PatronArriba:
		return esta_en_rango(t, p->x, p->y, patron_a_direccion(patron));
	case PatronAbajo:
		return esta_en_rango(t, p->x, p->y, patron_a_direccion(patron));
	case PatronDerecha:
		return esta_en_rango(t, p->x, p->y, patron_a_direccion(patron));
	case PatronIzquierda:
		return esta_en_rango(t, p->x, p->y, patron_a_direccion(patron));
	case PatronEspejo:
		return es_direccion_valida(t, p, t->jugador->ultimo_movimiento);
	case PatronInverso:
		return es_direccion_valida(
			t, p, direccion_inversa(t->jugador->ultimo_movimiento));
	case PatronRandom:
		return true; // siempre valido
	default:
		return false;
	}
}

bool es_direccion_valida(Tablero *t, Poke *p, Direccion d)
{
	return esta_en_rango(t, p->x, p->y, d);
}

bool esta_en_rango(Tablero *t, size_t x, size_t y, Direccion d)
{
	switch (d) {
	case Arriba:
		return y > 0;
	case Abajo:
		return y < t->alto - 1;
	case Derecha:
		return x < t->ancho - 1;
	case Izquierda:
		return x > 0;
	default:
		return false;
	}
}

// Movimientos Auxiliares
void mover_random(Tablero *t, Poke *p)
{
	while (true) {
		Direccion d = rand() % 4;
		if (esta_en_rango(t, p->x, p->y, d)) {
			mover_entidad(&p->x, &p->y, d);
			return;
		}
	}
}
