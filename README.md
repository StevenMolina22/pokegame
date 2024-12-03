## TP2: Juego de Captura de Pokémons

## Repositorio de (Marlon Stiven Molia Buitrago) - (112018) - (mmolinab@fi.uba.ar)

---
## Instrucciones de Compilación y Ejecución

### Compilación:
```bash
make tp2
```

### Ejecución:
```bash
./tp2 archivo.csv
```

### Ejecución con Valgrind:
```bash
./valgrind tp2 archivo.csv
```

---

## Introducción

El TP2 consiste en la implementación de un juego que simula un escenario de captura de Pokémon en un tablero de dimensiones **32x15**, con un límite de tiempo de 60 segundos. El jugador debe capturar Pokémon que se generan aleatoriamente en el tablero mientras estos se mueven según patrones específicos. El juego evalúa habilidades estratégicas del jugador a través de un sistema de puntuación y multiplicadores, incentivando la optimización de movimientos.

---

## Reglas y Mecánica del Juego

1. **Tablero y Jugador**:
   - El juego inicia con el jugador colocado en la primera celda del tablero.
   - El jugador puede moverse usando los cursores de dirección: Arriba, Abajo, Izquierda, Derecha.

2. **Pokémons**:
   - Al iniciar el juego, se generan **7 Pokémon aleatorios** tomados de un archivo CSV (pueden repetirse) y se posicionan aleatoriamente en el tablero.
   - Cada Pokémon tiene un patrón de movimiento único:
     - **N**: Arriba
     - **S**: Abajo
     - **E**: Derecha
     - **O**: Izquierda
     - **J**: Sigue los movimientos del jugador.
     - **I**: Movimiento opuesto al del jugador.
     - **R**: Movimiento aleatorio en una de las 4 direcciones.
   - Si el jugador no se mueve, los Pokémon tampoco.

3. **Captura y Puntuación**:
   - Un Pokémon es capturado al compartir la misma posición en el tablero que el jugador.
   - Al capturarlo:
     - El puntaje del Pokémon capturado se multiplica por el multiplicador actual del jugador.
     - Se genera un nuevo Pokémon aleatorio que reemplaza al capturado.
   - El multiplicador incrementa si el nombre o color del Pokémon capturado coincide con el último capturado; de lo contrario, se reinicia a 1.

4. **Fin del Juego**:
   - El juego finaliza cuando:
     - Se alcanza el límite de tiempo de **60 segundos**.
     - El jugador presiona la tecla `q` o `Q`.

---

## Menú Principal

El menú principal permite al usuario interactuar con el programa mediante las siguientes opciones obligatorias:

- **P (Pokedex):** Muestra los Pokémon cargados desde el archivo, ordenados alfabéticamente.
- **J (Jugar):** Inicia el juego con generación aleatoria de Pokémon.
- **S (Semilla):** Inicia el juego solicitando una semilla específica para controlar la aleatoriedad.
- **Q (Salir):** Termina la ejecución del programa.

Opciones adicionales (como elegir tableros o niveles de dificultad) son opcionales y pueden ser implementadas para enriquecer la experiencia del usuario.

---

## Estructura del Código

El programa se organiza en módulos independientes, cada uno con responsabilidades claras:

### 1. **TDA Juego**

Gestión principal del flujo del juego. Incluye datos sobre el estado del tablero, los Pokémon y el jugador.

**Responsabilidades**:
- Iniciar y finalizar el juego.
- Procesar movimientos del jugador y actualizar el tablero.
- Evaluar capturas y calcular puntajes.

**Operaciones Principales**:
- `juego_crear` / `juego_destruir`: Inicialización y liberación de recursos.
- `juego_iniciar`: Configuración inicial del juego.
- `juego_correr`: Procesamiento del juego durante cada turno.
- `juego_mostrar_resultados`: Despliegue de estadísticas finales.

---

### 2. **TDA Tablero**

Gestión del espacio de juego y la interacción entre el jugador y los Pokémon.

**Responsabilidades**:
- Controlar las posiciones del jugador y los Pokémon.
- Verificar capturas.
- Mostrar el estado actual del tablero.

**Operaciones Principales**:
- `tablero_crear` / `tablero_destruir`: Gestión de memoria para el tablero.
- `tablero_mover_jugador`: Procesar movimientos del jugador.
- `tablero_mover_pokes`: Actualizar la posición de los Pokémon según su patrón.
- `tablero_esta_capturado`: Verificar si un Pokémon fue capturado.

---

### 3. **TDA Pokedex**

Gestión de la lista de Pokémon disponibles en el juego.

**Responsabilidades**:
- Cargar Pokémon desde un archivo CSV.
- Generar Pokémon aleatorios en el tablero.
- Mostrar los datos de la Pokédex.

**Operaciones Principales**:
- `pokedex_crear` / `pokedex_destruir`: Gestión de memoria para la Pokédex.
- `pokedex_cargar_desde`: Carga de datos desde el archivo CSV.
- `pokedex_print`: Mostrar los Pokémon en pantalla.
- `pokedex_agregar_random`: Agregar Pokémon aleatorios al tablero.

---

### Estadísticas Finales

Al concluir el juego, se muestran los siguientes datos:
- **Puntaje total**: Puntos acumulados por capturas.
- **Máximo multiplicador**: Multiplicador más alto alcanzado durante el juego.
- **Combo más largo**: Secuencia más larga de capturas que incrementaron el multiplicador.

---

## Desarrollo Teórico

### Diseño Modular

- Cada TDA encapsula una responsabilidad específica, facilitando el mantenimiento y la ampliación del programa.
- Los TDAs reutilizados de trabajos anteriores se adaptaron para integrarse con las nuevas estructuras y reglas del juego.

---

## Ejemplo de Flujo de Juego

1. El usuario selecciona la opción **J** para iniciar el juego.
2. El jugador utiliza las teclas de dirección para moverse en el tablero.
3. Los Pokémon se mueven automáticamente según sus patrones.
4. Al capturar un Pokémon:
   - Se actualizan los puntos y el multiplicador.
   - Se genera un nuevo Pokémon en el tablero.
5. El juego termina tras **60 segundos** o al presionar `Q`.

---

## Decisiones de Diseño

1. **Estructura del Juego**:
   - Centralizar el flujo del juego en el TDA `Juego` para simplificar la lógica y facilitar las pruebas.

2. **Pokedex**:
   - Usar listas dinámicas para gestionar los Pokémon, permitiendo escalabilidad y simplicidad en la búsqueda.

3. **Patrones de Movimiento**:
   - Utilizar un sistema flexible basado en caracteres (`N`, `S`, etc.) que permite la expansión de patrones en el futuro.

---

## Diagrama de Arquitectura

```plaintext
+---------------------+
|        Juego        |
|---------------------|
| - Tablero           |
| - Pokedex           |
| - Tiempo inicio     |
|---------------------|
| + juego_iniciar()   |
| + juego_correr()    |
| + juego_terminar()  |
+---------------------+

+---------------------+
|       Tablero       |
|---------------------|
| - Jugador           |
| - Lista de Pokémon  |
|---------------------|
| + mover_jugador()   |
| + mover_pokemon()   |
| + mostrar_tablero() |
+---------------------+

+---------------------+
|       Pokedex       |
|---------------------|
| - Lista de Pokémon  |
|---------------------|
| + cargar_desde()    |
| + agregar_random()  |
| + mostrar()         |
+---------------------+
```
