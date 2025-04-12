#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include "producto.h"

typedef int (*ComparadorProducto)(const Producto *, const Producto *);

void selectionSortProductos(Producto arr[], int n, ComparadorProducto cmp);

#endif