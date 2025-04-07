#ifndef PRODUCTO_H
#define PRODUCTO_H

typedef struct {
    int id;
    char nombre[50];
    char categoria[30];
    double precio;
    int stock;
} Producto;

#endif