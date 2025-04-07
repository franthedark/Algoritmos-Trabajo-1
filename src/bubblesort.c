#include "bubblesort.h"

void swapProductos(Producto *a, Producto *b) {
    Producto temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortProductos(Producto arr[], int n) {
    int i, lastSwap, newRange;
    int swapped;
    newRange = n;

    do {
        swapped = 0;
        lastSwap = 0;
        for (i = 1; i < newRange; i++) {
            //compara el precio para ordenar de forma ascendente
            if (arr[i - 1].precio > arr[i].precio) {
                swapProductos(&arr[i - 1], &arr[i]);
                swapped = 1;
                lastSwap = i;  //actualiza el indice del ultimo intercambio
            }
        }
        newRange = lastSwap;  //reduce el rango para la proxima pasada
    } while (swapped); //si no hubo intercambio el arreglo está ordenado
}