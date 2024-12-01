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
