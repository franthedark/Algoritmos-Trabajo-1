#ifndef BUSBI_H
#define BUDBI_H

#include <stdio.h>
#include <string.h>
#include "producto.h"


int binarySearchRec (int X[],int l,int r,int key);//busqueda binaria recursiva
int binarySearchIt (int X[],int l,int r,int key );//busqueda binaria iterativa
int buscarPorNombreBinaria(Producto productos[],int n,const char* nombreBuscado); // busqueda binaria por nombre (el arreglo debe estar ordenado por nombre)
int buscarPorPrecioBinaria(Producto productos[],int n,double precioBuscado); /// busqueda binaria por precio (el arreglo debe estar ordenado porprecio)

#endif