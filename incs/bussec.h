#ifndef BUSSEC_H
#define BUSSEC_H

#include <stdio.h>
#include <string.h>
#include "producto.h"

int Bseq2(int v[], int x, int n); //busqueda secuencial
int SecBusxNom(Producto productos[], int n, const char* nombreB); //busqueda secuencial por nombre
void SecBuscarRangoPrecio(Producto productos[], int n, double min, double max);

#endif