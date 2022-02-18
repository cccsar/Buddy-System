# Buddy-System

Memory management simulator implementing [buddy system](https://en.wikipedia.org/wiki/Buddy_memory_allocation).

The simulator is interactive and supports instructions for allocating, releasing and showing the memory layout.

## Execution

To build run: `make`

To execute run: `./buddy <cantidad_de_memoria_a_manejar>` and interact.

Input can be one of:

* `RESERVAR <name> <amout>`: where `name` is the name of a tag asociated with `amount` memory. This reserves `amount` memory and associates it to `name` or throws an error if the tag exists or there is not enough contiguous memory.
* `LIBERAR <name>`: releases memory associated with name or gives an error if there's no such a tag named `name`.
* `MOSTRAR`: display memory layout and existing bindings.
* `SALIR`: exit program
