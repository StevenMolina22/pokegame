#include "tipos.h"

Color color_desde(char* s) {
    if (strcmp(s, "AMARILLO") == 0) {
	   return Amarillo;
	} else if (strcmp(s, "ROJO") == 0) {
	   return Rojo;
	} else if (strcmp(s, "AZUL") == 0) {
	   return Azul;
	} else if (strcmp(s, "MAGENTA") == 0) {
	   return Magenta;
	} else if (strcmp(s, "VERDE") == 0) {
	   return Verde;
	}
    return ERROR;
}

void str_desde(Color color, char* s) {
    switch (color) {
        case Azul:
            strcpy(s, "Azul");
            return;
        case Amarillo:
            strcpy(s, "Amarillo");
            return;
        case Magenta:
            strcpy(s, "Magenta");
            return;
        case Verde:
            strcpy(s, "Verde");
            return;
        case Rojo:
            strcpy(s, "Verde");
            return;
        case Rosa:
            strcpy(s, "Rosa");
            return;
    }
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
