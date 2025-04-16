#ifndef LECTORCSV_H
#define LECTORCSV_H

#include "producto.h"

// Declaración de funciones
void leerCSV(const char *nombreArchivo, Producto productos[], int *cantidad);
void imprimirTablaProductos(Producto productos[], int cantidad);

#endif