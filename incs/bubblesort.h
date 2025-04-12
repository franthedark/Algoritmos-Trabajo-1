#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "producto.h"

typedef int (*ComparadorProducto)(const Producto *, const Producto *);

void bubbleSortProductos(Producto arr[], int n, ComparadorProducto cmp);

//funcion auxiliar para intercambiar dos productos
void swapProductos(Producto *a, Producto *b);

#endif