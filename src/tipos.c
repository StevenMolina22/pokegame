#include "tipos.h"

Color color_desde(char* s) {
    if (strcmp(s, "AMARILLO")) {
	   return Amarillo;
	} else if (strcmp(s, "ROJO")) {
	   return Rojo;
	} else if (strcmp(s, "AZUL")) {
	   return Azul;
	} else if (strcmp(s, "MAGENTA")) {
	   return Magenta;
	} else if (strcmp(s, "VERDE")) {
	   return Verde;
	}
    return ERROR;
}
