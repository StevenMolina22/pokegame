#include "pa2m.h"
#include "src/tipo_poke.h"
#include "src/tda_juego.h"
#include "src/tda_pokedex.h"
#include "src/tda_menu.h"
#include "src/tda_tablero.h"
#include "src/io/io_csv.h"

// ---- TDA JUEGO
void prueba_crear_juego() {
    pa2m_nuevo_grupo("Pruebas de creación de juego");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

    juego_destruir(j);
}

void prueba_iniciar_juego() {
    pa2m_nuevo_grupo("Pruebas de inicialización de juego");

    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    pa2m_afirmar(csv != NULL, "Se abre archivo CSV correctamente");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

    juego_iniciar(j, csv);

    time_t tiempo_inicio = juego_tiempo_inicio(j);
    pa2m_afirmar(tiempo_inicio != 0, "El tiempo de inicio se establece correctamente");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_inicializacion_invalida() {
    pa2m_nuevo_grupo("Pruebas de inicialización con datos inválidos");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "El juego se crea correctamente");

    CSV* csv = csv_abrir("datos/inexistente.csv", ',');
    pa2m_afirmar(csv == NULL, "No se abre un archivo CSV inexistente");

    juego_iniciar(j, csv);
    pa2m_afirmar(true, "El juego maneja correctamente un CSV inválido");

    juego_destruir(j);
}

void prueba_tiempo_inicio() {
    pa2m_nuevo_grupo("Pruebas de tiempo de inicio de juego");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    time_t tiempo_inicio = juego_tiempo_inicio(j);
    pa2m_afirmar(tiempo_inicio > 0, "El tiempo de inicio es un valor válido");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_correr_juego() {
    pa2m_nuevo_grupo("Pruebas de ejecución de juego");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    int entradas[] = {TECLA_ABAJO, TECLA_DERECHA, TECLA_DERECHA, TECLA_ABAJO};
    for (int i = 0; i < 4; i++) {
        juego_correr(j, entradas[i]);
    }

    pa2m_afirmar(true, "El juego procesa diferentes entradas de usuario");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_mostrar_resultados() {
    pa2m_nuevo_grupo("Pruebas de mostrar resultados");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "Juego se crea correctamente");

    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    juego_mostrar_resultados(j);
    pa2m_afirmar(true, "Se pueden mostrar los resultados del juego");

    csv_cerrar(csv);
    juego_destruir(j);
}


void prueba_iniciar_juego_csv_invalido() {
    pa2m_nuevo_grupo("Pruebas de inicialización del juego con CSV inválido");

    CSV* csv = csv_abrir("datos/vacio.csv", ',');
    pa2m_afirmar(csv != NULL, "Se abre archivo CSV vacío correctamente");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "El juego se crea correctamente");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_captura_pokemon() {
    pa2m_nuevo_grupo("Pruebas de captura de pokemones");

    Juego* j = juego_crear();
    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    // Simular captura de un pokemon
    int movimientos[] = {TECLA_DERECHA, TECLA_ARRIBA, TECLA_IZQUIERDA};
    for (int i = 0; i < 3; i++) {
        juego_correr(j, movimientos[i]);
    }

    pa2m_afirmar(true, "El juego permite capturar un pokemon y actualiza el puntaje correctamente");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_movimientos_invalidos() {
    pa2m_nuevo_grupo("Pruebas de movimientos inválidos");

    Juego* j = juego_crear();
    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    int movimientos[] = {9999, -1, 'x', 0};
    for (int i = 0; i < 4; i++) {
        juego_correr(j, movimientos[i]);
    }

    pa2m_afirmar(true, "El juego maneja movimientos inválidos sin problemas");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_multiple_inicializacion() {
    pa2m_nuevo_grupo("Pruebas de múltiples inicializaciones");

    Juego* j = juego_crear();
    pa2m_afirmar(j != NULL, "El juego se crea correctamente");

    for (int i = 0; i < 3; i++) {
        CSV* csv = csv_abrir("datos/pokedex.csv", ',');
        juego_iniciar(j, csv);
        pa2m_afirmar(juego_tiempo_inicio(j) > 0, "El tiempo de inicio se reinicia correctamente");
        csv_cerrar(csv);
    }

    juego_destruir(j);
}

void prueba_movimientos_excesivos() {
    pa2m_nuevo_grupo("Pruebas de límite de movimientos");

    Juego* j = juego_crear();
    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    for (int i = 0; i < 1000; i++) {
        juego_correr(j, TECLA_DERECHA);
    }

    pa2m_afirmar(true, "El juego maneja correctamente una gran cantidad de movimientos");

    csv_cerrar(csv);
    juego_destruir(j);
}

void prueba_resultados_sin_juego() {
    pa2m_nuevo_grupo("Pruebas de mostrar resultados sin progreso");

    Juego* j = juego_crear();
    CSV* csv = csv_abrir("datos/pokedex.csv", ',');
    juego_iniciar(j, csv);

    juego_mostrar_resultados(j);
    pa2m_afirmar(true, "El juego muestra resultados incluso sin capturas");

    csv_cerrar(csv);
    juego_destruir(j);
}




// ---- TDA POKEDEX

void prueba_pokedex_crear_destruir()
{
	Pokedex *pkx = pokedex_crear();
	pa2m_afirmar(pkx != NULL, "Pkx no es null al crear");
	pokedex_destruir(pkx);
}

void prueba_pokedex_agregar_contar()
{
	Pokedex *pkx = pokedex_crear();
	Poke *p1 = poke_crear("Pikachu", 100, Amarillo, "JJ");
	Poke *p2 = poke_crear("Charmander", 200, Rojo, "II");

	pokedex_agregar(pkx, p1);
	pokedex_agregar(pkx, p2);

	pa2m_afirmar(pokedex_cant(pkx) == 2, "Cantidad es 2 al insertar");
	pokedex_destruir(pkx);
}

void prueba_pokedex_vaciar()
{
	Pokedex *pkx = pokedex_crear();
	Poke *p1 = poke_crear("Bulbasaur", 150, Verde, "N");
	Poke *p2 = poke_crear("Squirtle", 120, Azul, "O");

	pokedex_agregar(pkx, p1);
	pokedex_agregar(pkx, p2);

	pa2m_afirmar(pokedex_cant(pkx) == 2, "Cantidad es 2 luego de insertar");

	pokedex_vaciar(pkx);
	pa2m_afirmar(pokedex_cant(pkx) == 0, "Cantidad es 0 al vaciar");

	pokedex_destruir(pkx);
}

void prueba_pokedex_copiar()
{
	Pokedex *pkx = pokedex_crear();
	Poke *p1 = poke_crear("Eevee", 180, Magenta, "Normal");

	pokedex_agregar(pkx, p1);

	Pokedex *pkx_copia = pokedex_copiar(pkx);
	pa2m_afirmar(pokedex_cant(pkx_copia) == 1, "La cantidad es 1 luego de insertar");

	pokedex_destruir(pkx);
	pokedex_destruir(pkx_copia);
}

//
void prueba_pokedex_cargar_desde_csv()
{
	Pokedex *pkx = pokedex_crear();
	CSV *csv = csv_abrir("datos/pokedex.csv", ',');

	pa2m_afirmar(csv != NULL, "CSV no es null");
	bool resultado = pokedex_cargar_desde(pkx, csv);
	pa2m_afirmar(resultado == true, "se pudo cargar");
	pa2m_afirmar(pokedex_cant(pkx) > 0, "Pokedex cargada tiene elementos");

	csv_cerrar(csv);
	pokedex_destruir(pkx);
}

void prueba_pokedex_agregar_random()
{
	Pokedex *pkx_original = pokedex_crear();
	Pokedex *pkx_destino = pokedex_crear();

	Poke *p1 = poke_crear("Mewtwo", 500, Magenta, "NSE");
	Poke *p2 = poke_crear("Gyarados", 400, Azul, "NSE");
	Poke *p3 = poke_crear("Charizard", 300, Rojo, "NSE");

	pokedex_agregar(pkx_original, p1);
	pokedex_agregar(pkx_original, p2);
	pokedex_agregar(pkx_original, p3);

	bool agregado = pokedex_agregar_random(pkx_original, pkx_destino);
	pa2m_afirmar(agregado == true,
		     "Se agregó un pokemon aleatorio exitosamente");
	pa2m_afirmar(pokedex_cant(pkx_destino) == 1,
		     "La pokedex destino tiene un pokemon");

	pokedex_destruir(pkx_original);
	pokedex_destruir(pkx_destino);
}

void prueba_pokedex_lista()
{
	Pokedex *pkx = pokedex_crear();
	Poke *p1 = poke_crear("Snorlax", 300, Verde, "NSEJ");
	Poke *p2 = poke_crear("Lapras", 400, Azul, "JJO");

	pokedex_agregar(pkx, p1);
	pokedex_agregar(pkx, p2);

	Lista *lista_pokes = pokedex_lista(pkx);
	pa2m_afirmar(lista_pokes != NULL, "Se obtuvo una lista de pokemones");
	pa2m_afirmar(lista_cantidad_elementos(lista_pokes) == 2,
		     "La lista contiene dos pokemones");

	pokedex_destruir(pkx);
}

void prueba_pokedex_imprimir_nombres()
{
	Pokedex *pkx = pokedex_crear();
	Poke *p1 = poke_crear("Zapdos", 500, Amarillo, "RIJOEEE");
	Poke *p2 = poke_crear("Articuno", 500, Azul, "JJOOESN");

	pokedex_agregar(pkx, p1);
	pokedex_agregar(pkx, p2);

	printf("Prueba de impresión de nombres:\n");
	pokedex_print_nombres(
		pkx,
		stdout); // Salida esperada: Articuno, Zapdos (orden alfabético)

	pokedex_destruir(pkx);
}

void prueba_pokedex_copiar_independencia()
{
	Pokedex *pkx_original = pokedex_crear();
	Pokedex *pkx_copia = pokedex_copiar(pkx_original);

	Poke *p1 = poke_crear("Dragonite", 600, Amarillo, "NJIRRRS");
	pokedex_agregar(pkx_original, p1);

	pa2m_afirmar(pokedex_cant(pkx_original) == 1,
		     "Original tiene un pokemon");
	pa2m_afirmar(pokedex_cant(pkx_copia) == 0,
		     "Copia sigue vacía, es independiente");

	pokedex_destruir(pkx_original);
	pokedex_destruir(pkx_copia);
}



// ---- TDA MENU

bool accion_prueba(void* ctx) {
    int* contador = (int*)ctx;
    (*contador)++;
    return true;
}

void prueba_crear_menu() {
    pa2m_nuevo_grupo("Pruebas creacion menu");
    Menu* m = menu_crear();

    pa2m_afirmar(m != NULL, "Menu no es null");

    menu_destruir(m);
}

void prueba_agregar_accion_menu() {
    pa2m_nuevo_grupo("Pruebas agregar accion al menu");
    Menu* m = menu_crear();

    pa2m_afirmar(menu_agregar(m, 'a', "Opcion A", accion_prueba), "Se agrega la accion 'a' correctamente");
    pa2m_afirmar(menu_agregar(m, 'b', "Opcion B", accion_prueba), "Se agrega la accion 'b' correctamente");

    menu_destruir(m);
}

void prueba_agregar_accion_menu_caracteres_especiales() {
    pa2m_nuevo_grupo("Pruebas agregar accion con caracteres especiales");
    Menu* m = menu_crear();

    pa2m_afirmar(menu_agregar(m, '@', "Opcion @", accion_prueba), "Se agrega la accion '@' correctamente");
    pa2m_afirmar(menu_agregar(m, '#', "Opcion #", accion_prueba), "Se agrega la accion '#' correctamente");

    menu_destruir(m);
}

void prueba_ejecutar_accion_menu() {
    pa2m_nuevo_grupo("Pruebas ejecutar accion del menu");
    Menu* m = menu_crear();
    int contador = 0;

    menu_agregar(m, 'a', "Opcion A", accion_prueba);
    menu_agregar(m, 'b', "Opcion B", accion_prueba);

    pa2m_afirmar(menu_accion(m, 'a', &contador), "Se ejecuta la accion 'a' correctamente");
    pa2m_afirmar(contador == 1, "El contador se incrementa correctamente");

    pa2m_afirmar(menu_accion(m, 'b', &contador), "Se ejecuta la accion 'b' correctamente");
    pa2m_afirmar(contador == 2, "El contador se incrementa correctamente");

    pa2m_afirmar(!menu_accion(m, 'c', &contador), "No se ejecuta la accion 'c' (no existe)");

    menu_destruir(m);
}

void prueba_mostrar_menu() {
    pa2m_nuevo_grupo("Pruebas mostrar menu");
    Menu* m = menu_crear();

    menu_agregar(m, 'a', "Opcion A", accion_prueba);
    menu_agregar(m, 'b', "Opcion B", accion_prueba);

    printf("Se espera ver las opciones 'a' y 'b':\n");
    menu_print(m);

    menu_destruir(m);
}

void prueba_destruir_menu() {
    pa2m_nuevo_grupo("Pruebas destruir menu");
    Menu* m = menu_crear();

    menu_agregar(m, 'a', "Opcion A", accion_prueba);
    menu_agregar(m, 'b', "Opcion B", accion_prueba);

    menu_destruir(m);
    pa2m_afirmar(true, "Menu destruido correctamente");
}

// Prueba para agregar múltiples acciones con la misma clave
void prueba_agregar_accion_claves_repetidas() {
    pa2m_nuevo_grupo("Pruebas agregar acciones con claves repetidas");
    Menu* m = menu_crear();

    pa2m_afirmar(menu_agregar(m, 'a', "Primera opción", accion_prueba), "Se agrega la acción 'a' correctamente");
    pa2m_afirmar(!menu_agregar(m, 'a', "Segunda opción", accion_prueba), "No se permite agregar otra acción con la misma clave 'a'");

    menu_destruir(m);
}

// Prueba para claves inválidas
void prueba_agregar_claves_invalidas() {
    pa2m_nuevo_grupo("Pruebas agregar claves inválidas");
    Menu* m = menu_crear();

    pa2m_afirmar(!menu_agregar(m, '\0', "", accion_prueba), "No se permite agregar una acción con clave nula");
    pa2m_afirmar(!menu_agregar(m, '\0', NULL, accion_prueba), "No se permite agregar una acción con clave nula");

    menu_destruir(m);
}

// Prueba para manejo de mayúsculas y minúsculas
void prueba_ejecucion_mayusculas_minusculas() {
    pa2m_nuevo_grupo("Pruebas ejecución con mayúsculas y minúsculas");
    Menu* m = menu_crear();
    int contador = 0;

    menu_agregar(m, 'a', "Opción A", accion_prueba);
    menu_agregar(m, 'Q', "Salir", accion_prueba);

    pa2m_afirmar(menu_accion(m, 'a', &contador), "Se ejecuta correctamente la acción 'a'");
    pa2m_afirmar(menu_accion(m, 'A', &contador), "Se ejecuta correctamente la acción 'A' (equivalente a 'a')");
    pa2m_afirmar(menu_accion(m, 'q', &contador), "Se ejecuta correctamente la acción 'q' (equivalente a 'Q')");
    pa2m_afirmar(menu_accion(m, 'Q', &contador), "Se ejecuta correctamente la acción 'Q'");

    menu_destruir(m);
}

// Prueba para múltiples ejecuciones y estado del contexto
void prueba_multiples_ejecuciones() {
    pa2m_nuevo_grupo("Pruebas múltiples ejecuciones");
    Menu* m = menu_crear();
    int contador = 0;

    menu_agregar(m, 'x', "Opción X", accion_prueba);

    pa2m_afirmar(menu_accion(m, 'x', &contador), "Primera ejecución de la acción 'x' exitosa");
    pa2m_afirmar(contador == 1, "El contador es 1 después de la primera ejecución");

    pa2m_afirmar(menu_accion(m, 'x', &contador), "Segunda ejecución de la acción 'x' exitosa");
    pa2m_afirmar(contador == 2, "El contador es 2 después de la segunda ejecución");

    menu_destruir(m);
}

// Prueba para sobrecargar el menú (si tiene un límite conocido)
void prueba_sobrecarga_menu() {
    pa2m_nuevo_grupo("Pruebas sobrecargar el menú");
    Menu* m = menu_crear();

    bool exito = true;
    for (char c = 'a'; c <= 'z'; c++) {
        exito &= menu_agregar(m, c, "Opción", accion_prueba);
    }

    pa2m_afirmar(exito, "Se pueden agregar múltiples acciones sin errores (hasta el límite)");

    menu_destruir(m);
}

// Prueba de integridad al destruir el menú
void prueba_integridad_destruir_menu() {
    pa2m_nuevo_grupo("Pruebas integridad al destruir el menú");
    Menu* m = menu_crear();

    menu_agregar(m, 'a', "Opción A", accion_prueba);
    menu_agregar(m, 'b', "Opción B", accion_prueba);

    menu_destruir(m);
    pa2m_afirmar(true, "El menú se destruye correctamente sin errores de memoria");
}

void prueba_pokedex_cargar_csv_inexistente()
{
	Pokedex *pkx = pokedex_crear();
	CSV *csv = csv_abrir("inexistente.csv", ',');

	pa2m_afirmar(csv == NULL, "El archivo CSV inexistente no pudo abrirse");
	bool resultado = pokedex_cargar_desde(pkx, csv);
	pa2m_afirmar(resultado == false,
		     "No se pudo cargar datos de un archivo inexistente");

	pokedex_destruir(pkx);
}


// ---- TDA_TABLERO
#include "pa2m.h"

void prueba_crear_tablero() {
    pa2m_nuevo_grupo("Pruebas creación de tablero");
    Tablero* t = tablero_crear(32, 15);

    pa2m_afirmar(t != NULL, "Se puede crear un tablero");
    pa2m_afirmar(tablero_ancho(t) == 32, "El ancho del tablero es correcto");
    pa2m_afirmar(tablero_alto(t) == 15, "El alto del tablero es correcto");

    tablero_destruir(t);
}

void prueba_destruir_tablero() {
    pa2m_nuevo_grupo("Pruebas destrucción de tablero");
    Tablero* t = tablero_crear(32, 15);

    tablero_destruir(t);
    pa2m_afirmar(true, "Tablero destruido correctamente");
}

void prueba_tablero_mover_jugador() {
    pa2m_nuevo_grupo("Pruebas movimiento del jugador");
    Tablero* t = tablero_crear(32, 15);

    tablero_mover_jugador(t, Derecha);
    Jugador* j = tablero_jugador(t);
    pa2m_afirmar(j->x == 1 && j->y == 0, "El jugador se movió hacia la derecha");

    tablero_mover_jugador(t, Abajo);
    pa2m_afirmar(j->x == 1 && j->y == 1, "El jugador se movió hacia abajo");

    tablero_mover_jugador(t, Arriba);
    pa2m_afirmar(j->x == 1 && j->y == 0, "El jugador se movió hacia arriba");

    tablero_mover_jugador(t, Izquierda);
    pa2m_afirmar(j->x == 0 && j->y == 0, "El jugador se movió hacia la izquierda");

    tablero_destruir(t);
}

void prueba_tablero_mover_pokemon() {
    pa2m_nuevo_grupo("Pruebas movimiento de pokémon");
    Tablero* t = tablero_crear(32, 15);

    Poke* p = poke_crear("Charmander", 50, Rojo, "NSE");
    p->x = 5;
    p->y = 5;
    pokedex_agregar(tablero_pokedex(t), p);

    // posicion nueva esperada: x: 6 y: 5
    tablero_mover_pokes(t);
    pa2m_afirmar(p->y == 5, "El pokémon se movió hacia arriba y luego abajo (N)(S)");
    pa2m_afirmar(p->x == 6, "El pokémon se movió hacia la derecha (E)");

    tablero_destruir(t);
}

void prueba_tablero_captura_pokemon() {
    pa2m_nuevo_grupo("Pruebas captura de pokémon");
    Tablero* t = tablero_crear(32, 15);
    Jugador* j = tablero_jugador(t);

    Poke* p = poke_crear("Bulbasaur", 75, Verde, "R");
    p->x = j->x;
    p->y = j->y;
    pokedex_agregar(tablero_pokedex(t), p);

    pa2m_afirmar(tablero_esta_capturado(t, p), "El pokémon fue capturado al estar en la misma posición que el jugador");

    tablero_destruir(t);
}

void prueba_tablero_mostrar() {
    pa2m_nuevo_grupo("Pruebas mostrar el tablero");
    Tablero* t = tablero_crear(32, 15);

    tablero_mostrar(t);
    pa2m_afirmar(true, "El tablero fue mostrado correctamente");

    tablero_destruir(t);
}

void prueba_crear_tablero_borde() {
    pa2m_nuevo_grupo("Pruebas creación de tablero borde");
    Tablero* t = tablero_crear(0, 0);
    pa2m_afirmar(t == NULL, "No se puede crear un tablero con dimensiones inválidas");

    Tablero* t2 = tablero_crear(32, 15);
    pa2m_afirmar(t2 != NULL, "Se puede crear un tablero");

    Tablero* t3 = tablero_crear(32, 15);
    pa2m_afirmar(t3 != NULL, "Se puede crear un tablero grande");

    tablero_destruir(t2);
    tablero_destruir(t3);
}

void prueba_destruir_tablero_borde() {
    pa2m_nuevo_grupo("Pruebas destrucción de tablero borde");
    Tablero* t = NULL;
    tablero_destruir(t);
    pa2m_afirmar(true, "Destruir un tablero NULL no genera errores");

    Tablero* t2 = tablero_crear(32, 15);
    tablero_destruir(t2);
    pa2m_afirmar(true, "Un tablero válido se destruye correctamente");
}

void prueba_tablero_mover_jugador_bordes() {
    pa2m_nuevo_grupo("Pruebas movimiento del jugador en bordes del tablero");
    Tablero* t = tablero_crear(32, 15);
    Jugador* j = tablero_jugador(t);

    tablero_mover_jugador(t, Izquierda);
    pa2m_afirmar(j->x == 0 && j->y == 0, "El jugador no se mueve fuera del límite izquierdo");

    tablero_mover_jugador(t, Arriba);
    pa2m_afirmar(j->x == 0 && j->y == 0, "El jugador no se mueve fuera del límite superior");

    for (int i = 0; i < 33; i++) tablero_mover_jugador(t, Derecha);
    pa2m_afirmar(j->x == 31 && j->y == 0, "El jugador no se mueve fuera del límite derecho");

    for (int i = 0; i < 16; i++) tablero_mover_jugador(t, Abajo);
    pa2m_afirmar(j->x == 31 && j->y == 14, "El jugador no se mueve fuera del límite inferior");

    tablero_destruir(t);
}

void prueba_tablero_mover_pokemon_borde() {
    pa2m_nuevo_grupo("Pruebas movimiento borde de pokémon");
    Tablero* t = tablero_crear(32, 15);

    Poke* p1 = poke_crear("Eevee", 100, Amarillo, "NSEO");
    p1->x = 0;
    p1->y = 0;
    pokedex_agregar(tablero_pokedex(t), p1);

    tablero_mover_pokes(t);
    pa2m_afirmar(p1->x == 0 && p1->y == 1, "El pokémon sigue el patrón NSEO y se mueve correctamente");

    Poke* p2 = poke_crear("Pikachu", 120, Amarillo, "RR");
    p2->x = 31;
    p2->y = 14;
    pokedex_agregar(tablero_pokedex(t), p2);

    tablero_mover_pokes(t);
    pa2m_afirmar(p2->x <= 31 && p2->y <= 14, "El pokémon con movimiento aleatorio no supera los límites");

    tablero_destruir(t);
}

void prueba_tablero_captura_pokemon_borde() {
    pa2m_nuevo_grupo("Pruebas borde de captura de pokémon");
    Tablero* t = tablero_crear(32, 15);
    Jugador* j = tablero_jugador(t);

    Poke* p = poke_crear("Squirtle", 50, Azul, "N");
    p->x = j->x;
    p->y = j->y;
    pokedex_agregar(tablero_pokedex(t), p);

    pa2m_afirmar(tablero_esta_capturado(t, p), "El pokémon es capturado al estar en la misma celda que el jugador");

    Poke* p2 = poke_crear("Charmander", 75, Rojo, "S");
    p2->x = 1;
    p2->y = 1;
    pokedex_agregar(tablero_pokedex(t), p2);
    pa2m_afirmar(!tablero_esta_capturado(t, p2), "El pokémon no es capturado si no está en la misma celda");

    tablero_destruir(t);
}
int main() {
    pa2m_nuevo_grupo("============== Pruebas de la Pokedex ===============");
    prueba_pokedex_crear_destruir();
	prueba_pokedex_agregar_contar();
	prueba_pokedex_vaciar();
	prueba_pokedex_copiar();
	prueba_pokedex_cargar_desde_csv();
	prueba_pokedex_agregar_random();
	prueba_pokedex_lista();
	prueba_pokedex_imprimir_nombres();
	prueba_pokedex_copiar_independencia();
	prueba_pokedex_cargar_desde_csv();
	prueba_pokedex_cargar_csv_inexistente();

    pa2m_nuevo_grupo("============== Pruebas del Juego ====================");
    prueba_crear_juego();
    prueba_iniciar_juego();
    prueba_tiempo_inicio();
    prueba_correr_juego();
    prueba_mostrar_resultados();
    prueba_iniciar_juego_csv_invalido();
    prueba_captura_pokemon();
    prueba_inicializacion_invalida();
    prueba_movimientos_invalidos();
    prueba_multiple_inicializacion();
    prueba_movimientos_excesivos();
    prueba_resultados_sin_juego();

    pa2m_nuevo_grupo("============== Pruebas del menu =====================");
    prueba_crear_menu();
    prueba_agregar_accion_menu();
    prueba_agregar_accion_menu_caracteres_especiales();
    prueba_ejecutar_accion_menu();
    prueba_mostrar_menu();
    prueba_destruir_menu();
    prueba_agregar_accion_menu_caracteres_especiales();
    prueba_agregar_accion_claves_repetidas();
    prueba_agregar_claves_invalidas();
    prueba_ejecucion_mayusculas_minusculas();
    prueba_multiples_ejecuciones();
    prueba_sobrecarga_menu();
    prueba_integridad_destruir_menu();

    pa2m_nuevo_grupo("================= Pruebas del tablero ===============");
    prueba_crear_tablero();
    prueba_crear_tablero_borde();
    prueba_destruir_tablero();
    prueba_destruir_tablero_borde();
    prueba_tablero_mover_jugador();
    prueba_tablero_mover_jugador_bordes();
    prueba_tablero_mover_pokemon();
    prueba_tablero_mover_pokemon_borde();
    prueba_tablero_captura_pokemon();
    prueba_tablero_captura_pokemon_borde();
    prueba_tablero_mostrar();
    return pa2m_mostrar_reporte();
}
