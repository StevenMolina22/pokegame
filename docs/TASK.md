# Task List for Pokegame Refactor

## TODO
- [ ] **Refactor Directory Structure**
  - Move all TDA-related files into a dedicated `tda/` directory.
  - Group IO-related files under `io/` consistently.
  - Organize utility files into a `utils/` directory.

- [ ] **Simplify TDA Interfaces**
  - Reduce exposed functions in `tda_juego.h`, `tda_tablero.h`, and `tda_pokedex.h` to essential operations.
  - Encapsulate internal logic in private headers (e.g., `tda_juego_priv.h`).

- [ ] **Improve Error Handling**
  - Standardize error codes across all TDAs using a shared `error.h` enum.
  - Add logging for critical failures in `juego_correr` and `csv_abrir`.

- [ ] **Modularize Game Loop**
  - Extract `game_loop` logic from `opciones_menu.c` into a separate `game_loop.c` module.
  - Define a clear interface for input handling in `game_loop.h`.

- [ ] **Enhance CSV Parsing**
  - Add validation for CSV column types in `poke_leer`.
  - Implement a buffer size check to prevent overflow in `csv_leer_linea`.

- [ ] **Optimize Pokedex Storage**
  - Replace `Lista` with a more efficient `abb_t` for sorted operations in `pokedex.c`.
  - Cache random Pokémon selections to reduce redundant copies.

- [ ] **Add Configuration File**
  - Create a `config.h` for game constants (e.g., `ANCHO`, `ALTO`, `TIEMPO_MAX`).
  - Allow runtime configuration via a `.ini` file for board size and Pokémon count.

- [ ] **Improve Memory Management**
  - Add reference counting for `Poke` structs shared between `Pokedex` and `Tablero`.
  - Audit `poke_copiar` and `pokedex_copiar` for deep copy leaks.

- [ ] **Document Public APIs**
  - Add Doxygen comments to all public functions in `tda_*.h` files.
  - Generate API documentation and store in `docs/api/`.

- [ ] **Unit Test Expansion**
  - Write tests for edge cases in `tablero_mover_pokes` and `verificar_capturas`.
  - Integrate a testing framework (e.g., Check) for automated runs.

- [ ] **Add Save/Load Functionality**
  - Implement `juego_guardar` to serialize game state to a JSON file.
  - Implement `juego_cargar` to restore game state from JSON.

- [ ] **Refactor Display Logic**
  - Move `tablero_mostrar` formatting to a separate `display.c` module.
  - Support customizable display themes via a `theme.h` configuration.

- [ ] **Internationalization Support**
  - Extract all user-facing strings to a `locale/en.json` file.
  - Add a `locale.c` module to load translations dynamically.
