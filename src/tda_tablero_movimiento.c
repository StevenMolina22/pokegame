#include "tda_tablero.h"
#include "tda_tablero_priv.h"
#include "tipos.h"

// ---- INTERFAZ TDA
void tablero_mover_jugador(Tablero* t, Direccion d) {
    if (t == NULL) {
        return;
    }
    if (entrada_es_valida(t, d)) {
        mover_entidad(&t->jugador->x, &t->jugador->y, d);
    }
    t->jugador->ultimo_movimiento = d;
}

void tablero_mover_pokes(Tablero* t) {
    if (t == NULL) {
        return;
    }
    // TODO!: Implementar iterando sobre la pokedex
}


// ---- AUXILIARES
void tablero_mover_poke(Tablero *t, Poke *p, Patron patron) {
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
            break;
        case PatronRandom:
            break;
    }
}

void mover_entidad(size_t *x, size_t *y, Direccion d) {
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


bool entrada_es_valida(Tablero* t, Direccion d) {
    return esta_en_rango(t, t->jugador->x, t->jugador->y, d);
}

bool es_direccion_valida(Tablero* t, Poke* p, Direccion d) {
    return esta_en_rango(t, p->x, p->y, d);
}

bool esta_en_rango(Tablero* t, size_t x, size_t y, Direccion d) {
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
void mover_random(Poke* p) {
    // TODO!
}

Direccion direccion_inversa(Direccion d) {
    switch (d) {
        case Arriba:
            return Abajo;
        case Abajo:
            return Arriba;
        case Derecha:
            return Izquierda;
        case Izquierda:
            return Derecha;
        default:
            return ERROR;
    }
}

// conversiones
Direccion patron_a_direccion(Patron p) {
    switch (p) {
    case PatronArriba:
        return Arriba;
    case PatronAbajo:
        return Abajo;
    case PatronDerecha:
        return Derecha;
    case PatronIzquierda:
        return Izquierda;
    default:
        return ERROR;
    }
}

Direccion tecla_a_direccion(Tecla t) {
    switch (t) {
        case TeclaArriba:
            return Arriba;
        case TeclaAbajo:
            return Abajo;
        case TeclaDerecha:
            return Derecha;
        case TeclaIzquierda:
            return Izquierda;
        default:
            return ERROR;
    }
}
