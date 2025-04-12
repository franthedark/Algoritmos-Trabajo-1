#include "bubblesort.h"

void swapProductos(Producto *a, Producto *b) {
    Producto temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortProductos(Producto arr[], int n, ComparadorProducto cmp) {
    int i, lastSwap, newRange;
    int swapped;
    newRange = n; //rango efectivo a recorrer en cada pasada

    do {
        swapped = 0;
        lastSwap = 0;
        for (i = 1; i < newRange; i++) {
            //se utiliza la funcion comparadora para decidir si se debe intercambiar
            if (cmp(&arr[i - 1], &arr[i]) > 0) {
                swapProductos(&arr[i - 1], &arr[i]);
                swapped = 1;
                lastSwap = i;  //actualiza el indice del ultimo intercambio
            }
        }
        newRange = lastSwap;  //reduce el rango para la proxima pasada
    } while (swapped); //si no hubo intercambios el arreglo está ordenado
}