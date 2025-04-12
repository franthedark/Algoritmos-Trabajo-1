#ifndef COMPARADORES_H
#define COMPARADORES_H

#include "producto.h"
#include <string.h>

typedef int (*ComparadorProducto)(const Producto *, const Producto *);

int compararPorId(const Producto *a, const Producto *b);

int compararPorNombre(const Producto *a, const Producto *b);

int compararPorCategoria(const Producto *a, const Producto *b);

int compararPorPrecio(const Producto *a, const Producto *b);

int compararPorStock(const Producto *a, const Producto *b);

#endif