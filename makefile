VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CFLAGSDEBUG =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g
ENGINECFLAGS =-Wall -Werror -O2 -g
CC = gcc

all: clean valgrind-alumno valgrind-tp2

valgrind-alumno: pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.c pruebas_alumno.c engine
	$(CC) $(CFLAGSDEBUG) src/*.c src/abb/*.c src/lista/*.c src/hash/*.c src/io/*.c pruebas_alumno.c engine.o -o pruebas_alumno

test_build: src/*.c tests/*.c
	$(CC) $(CFLAGSDEBUG) src/*.c src/abb/*.c src/lista/*.c src/hash/*.c src/io/*.c  tests/tda_juego_test.c engine.o -o pruebas_juego
	$(CC) $(CFLAGSDEBUG) src/*.c src/abb/*.c src/lista/*.c src/hash/*.c src/io/*.c  tests/tda_pokedex_test.c engine.o -o pruebas_pokedex
	$(CC) $(CFLAGSDEBUG) src/*.c src/abb/*.c src/lista/*.c src/hash/*.c src/io/*.c  tests/tda_tablero_test.c engine.o -o pruebas_tablero
	$(CC) $(CFLAGSDEBUG) src/*.c src/abb/*.c src/lista/*.c src/hash/*.c src/io/*.c  tests/tda_menu_test.c engine.o -o pruebas_menu

test: test_build
	valgrind $(VALGRIND_FLAGS) ./pruebas_pokedex
	valgrind $(VALGRIND_FLAGS) ./pruebas_tablero
	valgrind $(VALGRIND_FLAGS) ./pruebas_menu
	valgrind $(VALGRIND_FLAGS) ./pruebas_juego


valgrind-tp2: tp2
	valgrind $(VALGRIND_FLAGS) --verbose ./tp2 datos/pokedex.csv
	# ./tp2 datos/pokedex.csv

engine:
	$(CC) $(ENGINECFLAGS) -c extra/engine.c -o engine.o

tp2: engine
	$(CC) $(CFLAGS) src/*.c src/abb/*.c src/lista/*.c src/hash/*.c src/io/*.c tp2.c engine.o -o tp2

tp2-debug: engine
	$(CC) $(CFLAGSDEBUG) src/*.c src/abb/*.c src/lista/*.c src/hash/*.c src/io/*.c tp2.c engine.o -o tp2

debug: tp2-debug
	gdb --args ./tp2 datos/pokedex.csv

clean:
	rm -f pruebas_alumno tp2 engine.o
