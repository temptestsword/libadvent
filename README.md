# libadvent
`libadvent` is a small C library to make text based adventure games.

> [!WARNING]
> Currently this project is very very simple, and often faces breaking changes *every day*

## Fnctionalities
1. SImple colored outputs
2. Minimal Inventory and Quest systems
3. Expandable modular combatScene() and other functions
4. Easy to understand player and entity structs.

## Setup guide

`libadvent` uses an unity build system. the actual header file, `lib/libadvent.h` is not supposed to be included directly, but `src/libadv.c` is.

`libadv.c` acts as a *aggregate source* or *entry point* that includes `libadvent.h` and other semi-game specific functions. 

This allows you to compile everything into a single translation unit, reducing the overhead of multiple object files and improving compilation time.

Look at the `src/` folder for source demo and `Makefile` for a simple build system.

### Licence
Licenced under the MIT licence.
