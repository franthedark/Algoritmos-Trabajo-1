#ifndef PRODUCTO_H
#define PRODUCTO_H

typedef struct {
    int id;
    char nombre[50];
    char categoria[30];
    double precio;
    int stock;
} Producto;

// Declaración de funciones auxiliares
void imprimirProducto(const Producto *p);

#endif