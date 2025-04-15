VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CFLAGSDEBUG =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g
ENGINECFLAGS =-Wall -Werror -O2 -g
CC = gcc
FILES = src/*.c src/io/*.c src/lista/*.c src/abb/*.c src/hash/*.c

all: run clean
test: tests-run clean

engine:
	@$(CC) $(ENGINECFLAGS) -c extra/engine.c -o engine.o

# TESTS
tests: engine
	@$(CC) $(CFLAGS) $(FILES) pruebas_alumno.c engine.o -o pruebas_alumno

tests-run: tests
	@valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

# TP2
build: engine
	@$(CC) $(CFLAGS) $(FILES) tp2.c engine.o -o tp2

debug: engine
	@$(CC) $(FILES) $(CFLAGSDEBUG) tp2.c engine.o -o tp2

run: build
	@./tp2 datos/pokedex.csv

run-valgrind: build
	@valgrind $(VALGRIND_FLAGS) ./tp2 datos/pokedex.csv

run-debug: debug
	@gdb --args ./tp2 datos/pokedex.csv

clean:
	@rm -f pruebas_alumno tp2 engine.o
