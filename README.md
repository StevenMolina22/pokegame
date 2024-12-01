# TP 2

## Repositorio de (Nombre Apellido) - (Padrón) - (Mail)

- Para compilar:

```bash
gcc -o tp2 tp2.c src/*.c extra/*.c -Iinclude
```

- Para ejecutar:

```bash
./tp2 archivo.csv
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full ./tp2 archivo.csv
```
---
##  Funcionamiento

El TP2 consiste en la implementación de un juego en el que el jugador se mueve en un tablero de 32x15 casilleros y debe capturar pokemones que se generan aleatoriamente en el tablero. El juego tiene un tiempo límite de 60 segundos y se puede finalizar anticipadamente presionando la tecla 'q'.

### Estructuras desarrolladas

#### TDA Juego
El TDA `Juego` es el núcleo del programa y se encarga de gestionar el estado del juego, incluyendo el tablero, el jugador y los pokemones. Sus responsabilidades incluyen iniciar el juego, procesar las entradas del jugador, mover los pokemones, verificar capturas y mostrar los resultados al finalizar el juego.

**Datos:**
- `Tablero* tablero`: Estructura que contiene el estado del tablero, el jugador y los pokemones.
- `size_t semilla`: Semilla utilizada para la generación aleatoria.
- `time_t tiempo_inicio`: Tiempo en el que se inició el juego.

**Operaciones:**
- `Juego* juego_crear()`: Crea e inicializa la estructura del juego.
- `void juego_destruir(Juego* j)`: Destruye el juego y libera la memoria asociada.
- `void juego_iniciar(Juego* j, CSV* csv)`: Inicia las condiciones necesarias para el juego.
- `void juego_correr(Juego* j, int entrada)`: Procesa las entradas del jugador y actualiza el estado del juego.
- `void juego_terminar(Juego* j)`: Termina el juego.
- `void juego_mostrar_resultados(Juego* j)`: Muestra las estadísticas del jugador al finalizar el juego.
- `time_t juego_tiempo_inicio(Juego* j)`: Devuelve el tiempo en el que se inició el juego.

#### TDA Tablero
El TDA `Tablero` se encarga de gestionar el estado del tablero, incluyendo la posición del jugador y los pokemones. Sus responsabilidades incluyen mover al jugador, mover los pokemones y verificar si un pokemon ha sido capturado.

**Datos:**
- `Jugador* jugador`: Estructura que contiene el estado del jugador.
- `Pokedex* pokedex`: Estructura que contiene la lista de pokemones en el tablero.
- `size_t ancho`: Ancho del tablero.
- `size_t alto`: Alto del tablero.

**Operaciones:**
- `Tablero* tablero_crear(size_t ancho, size_t alto, Jugador* jugador, Pokedex* pokedex)`: Crea e inicializa la estructura del tablero.
- `void tablero_destruir(Tablero* t)`: Destruye el tablero y libera la memoria asociada.
- `void tablero_mover_jugador(Tablero* t, Direccion d)`: Mueve al jugador en la dirección especificada.
- `void tablero_mover_pokes(Tablero* t)`: Mueve a los pokemones según sus patrones de movimiento.
- `bool tablero_esta_capturado(Tablero* t, Poke* p)`: Verifica si un pokemon ha sido capturado por el jugador.
- `void tablero_mostrar(Tablero* t)`: Muestra el estado actual del tablero.

#### TDA Pokedex
El TDA `Pokedex` se encarga de gestionar la lista de pokemones disponibles en el juego. Sus responsabilidades incluyen cargar los pokemones desde un archivo CSV, agregar nuevos pokemones al tablero y mostrar la lista de pokemones.

**Datos:**
- `Lista* lista`: Lista de pokemones.

**Operaciones:**
- `Pokedex* pokedex_crear()`: Crea e inicializa la estructura de la pokedex.
- `void pokedex_destruir(Pokedex* p)`: Destruye la pokedex y libera la memoria asociada.
- `void pokedex_cargar_desde(Pokedex* p, CSV* csv)`: Carga los pokemones desde un archivo CSV.
- `void pokedex_agregar(Pokedex* p, Poke* poke)`: Agrega un pokemon a la pokedex.
- `void pokedex_agregar_random(Pokedex* p)`: Agrega un pokemon aleatorio al tablero.
- `void pokedex_print(Pokedex* p, FILE* stream)`: Muestra la lista de pokemones en el stream especificado.

### Funcionamiento general

El programa comienza leyendo un archivo CSV que contiene la información de los pokemones. Luego, se muestra un menú principal con las opciones de mostrar la pokedex, iniciar el juego, iniciar el juego con una semilla específica o salir del juego.

Al iniciar el juego, se coloca al jugador en el primer casillero del tablero y se generan 7 pokemones aleatorios en posiciones aleatorias del tablero. El jugador puede moverse utilizando los cursores y cada vez que se mueve, los pokemones también se mueven según sus patrones de movimiento.

El juego finaliza cuando se alcanza el tiempo límite de 60 segundos o cuando el jugador presiona la tecla 'q'. Al finalizar el juego, se muestran las estadísticas del jugador, incluyendo el puntaje alcanzado, el multiplicador máximo y el combo más largo realizado.

### Decisiones tomadas

- Se decidió utilizar una estructura `Juego` para gestionar el estado del juego y facilitar la separación de responsabilidades.
- Se implementaron funciones auxiliares para procesar las entradas del jugador, verificar capturas y actualizar el estado del juego.
- Se utilizó una lista para gestionar la pokedex y facilitar la adición y eliminación de pokemones.
- Se implementaron pruebas para cada TDA creado para asegurar su correcto funcionamiento.

### Diagramas

#### Diagrama de memoria

El siguiente diagrama muestra la estructura de memoria del juego:

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

#### Ejemplo de código

El siguiente fragmento de código muestra cómo se utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` se guarda en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```

<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---
