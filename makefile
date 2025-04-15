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
	@$(CC) $(CFLAGS) $(FILES) tests.c engine.o -o tests

tests-run: tests
	@valgrind $(VALGRIND_FLAGS) ./tests

# TP2
build: engine
	@$(CC) $(CFLAGS) $(FILES) pokegame.c engine.o -o pokegame

debug: engine
	@$(CC) $(FILES) $(CFLAGSDEBUG) pokegame.c engine.o -o tp2

run: build
	@./pokegame datos/pokedex.csv

run-valgrind: build
	@valgrind $(VALGRIND_FLAGS) ./pokegame datos/pokedex.csv

run-debug: debug
	@gdb --args ./pokegame datos/pokedex.csv

clean:
	@rm -f tests pokegame engine.o
