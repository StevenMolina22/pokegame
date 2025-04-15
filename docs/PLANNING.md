# Planning for Pokegame Refactor

## Project Vision
The goal is to transform Pokegame into a modular, extensible, and maintainable codebase suitable for inclusion in a portfolio. The refactored project will prioritize clean architecture, ease of modification, and LLM-friendly documentation to facilitate future enhancements and showcase robust software design principles.

## Objectives
1. **Modularity**: Break down the monolithic structure into smaller, reusable modules with clear responsibilities.
2. **Extensibility**: Design interfaces that allow easy addition of new features, such as new Pokémon behaviors or game modes.
3. **Maintainability**: Improve error handling, documentation, and testing to reduce bugs and ease debugging.
4. **Scalability**: Optimize data structures and algorithms to support larger game boards or more Pokémon without performance degradation.
5. **User Experience**: Enhance configurability and internationalization to make the game more accessible and customizable.

## Key Improvements
### 1. Codebase Organization
- **Unified TDA Directory**: Consolidate all TDAs (`juego`, `tablero`, `pokedex`, etc.) under `src/tda/` to reduce clutter and improve discoverability.
- **Utility Module**: Group generic utilities (`io_utils`, `str_split`, etc.) into `src/utils/` for reusability across projects.
- **Clear Separation of Concerns**: Ensure each module (e.g., `game_loop`, `display`) has a single responsibility, reducing coupling.

### 2. Simplified Interfaces
- **Minimal Public APIs**: Expose only essential functions in public headers, moving helper functions to private headers (e.g., `tda_juego_priv.h`).
- **Standardized Error Handling**: Introduce a shared `error.h` with consistent error codes and logging for all TDAs.
- **Configuration Layer**: Centralize constants (e.g., board size, game duration) in a `config.h` file, with optional runtime overrides via a `.ini` file.

### 3. Performance Optimization
- **Efficient Data Structures**: Replace `Lista` in `Pokedex` with `abb_t` for faster sorted access and reduce memory overhead in `poke_copiar`.
- **Memory Management**: Implement reference counting for shared `Poke` instances to prevent leaks and optimize deep copies.
- **Lazy Initialization**: Cache random Pokémon selections in `pokedex_agregar_random` to avoid redundant computations.

### 4. Extensibility
- **Pluggable Behaviors**: Introduce a `behavior.h` interface for Pokémon movement patterns, allowing new patterns without modifying core logic.
- **Game Modes**: Design a `game_mode.h` interface to support variants (e.g., timed mode, endless mode) with minimal code changes.
- **Save/Load System**: Add JSON-based serialization for game state, enabling features like pausing or replaying games.

### 5. Developer Experience
- **Comprehensive Documentation**: Use Doxygen to document all public APIs, generating browsable HTML docs in `docs/api/`.
- **Automated Testing**: Expand unit tests with a framework like Check, covering edge cases in movement, capture, and CSV parsing.
- **LLM-Friendly Artifacts**: Maintain `TASK.md` and `PLANNING.md` as living documents, with granular tasks and clear rationales for LLMs to parse and extend.

### 6. User-Facing Enhancements
- **Customizable Display**: Move rendering logic to a `display.c` module, supporting themes (e.g., ASCII vs. emoji) via `theme.h`.
- **Internationalization**: Extract strings to `locale/*.json` files, enabling multi-language support with a `locale.c` loader.
- **Flexible Input**: Abstract input handling in `game_loop.c` to support alternative controls (e.g., WASD, gamepad).

## Roadmap
1. **Phase 1: Restructure and Document (1-2 weeks)**
   - Reorganize directories and consolidate TDAs.
   - Add Doxygen comments and generate initial API docs.
   - Create `config.h` and standardize error handling.

2. **Phase 2: Optimize and Test (2-3 weeks)**
   - Refactor `Pokedex` to use `abb_t` and optimize memory usage.
   - Expand unit tests for critical paths (movement, captures).
   - Implement reference counting for `Poke` structs.

3. **Phase 3: Extend and Enhance (2-4 weeks)**
   - Add save/load functionality with JSON serialization.
   - Introduce pluggable behaviors and game modes.
   - Implement internationalization and customizable display themes.

## Success Criteria
- Codebase compiles without warnings and passes Valgrind checks.
- All public APIs are documented with Doxygen, and docs are published.
- Unit tests cover at least 80% of critical functions.
- Game supports at least one new feature (e.g., save/load, new mode) without breaking existing functionality.
- `TASK.md` and `PLANNING.md` are updated to reflect completed work and future plans.

## Risks and Mitigations
- **Complexity Creep**: Limit new features to those that align with modularity goals; defer non-essential ideas to future iterations.
- **Performance Regressions**: Profile key functions (e.g., `tablero_mover_pokes`) before and after optimizations.
- **LLM Misinterpretation**: Write clear, atomic tasks in `TASK.md` and avoid ambiguous terms in `PLANNING.md`.
