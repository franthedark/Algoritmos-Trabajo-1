#include "comparadores.h"

//compara dos productos por ID (ascendente)
int compararPorId(const Producto *a, const Producto *b) {
    return a->id - b->id;
}

//compara dos productos por nombre (ascendente)
int compararPorNombre(const Producto *a, const Producto *b) {
    return strcmp(a->nombre, b->nombre);
}

//compara dos productos por categoria (ascendente)
int compararPorCategoria(const Producto *a, const Producto *b) {
    return strcmp(a->categoria, b->categoria);
}

// compara dos productos por precio (ascendente)
int compararPorPrecio(const Producto *a, const Producto *b) {
    if(a->precio < b->precio)
        return -1;
    else if(a->precio > b->precio)
        return 1;
    return 0;
}

//compara dos productos por stock (ascendente)
int compararPorStock(const Producto *a, const Producto *b) {
    return a->stock - b->stock;
}