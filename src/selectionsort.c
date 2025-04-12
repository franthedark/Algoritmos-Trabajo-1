#include "selectionsort.h"

void selectionSortProductos(Producto arr[], int n, ComparadorProducto cmp) {
    int i, j, minIndex, maxIndex;
    Producto temp;
    
    //se recorre solo hasta la mitad del arreglo
    for (i = 0; i < n / 2; i++) {
        minIndex = i;
        maxIndex = i;
        
        //se busca el elemento minimo y maximo en la porcion no ordenada
        for (j = i; j < n - i; j++) {
            if (cmp(&arr[j], &arr[minIndex]) < 0)
                minIndex = j;
            if (cmp(&arr[j], &arr[maxIndex]) > 0)
                maxIndex = j;
        }
        
        //se intercambia el elemento minimo con el elemento en la posicion i, si es necesario
        if (minIndex != i) {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            //si el elemento maximo se encontraba en la posición i, se actualiza su índice
            if (maxIndex == i)
                maxIndex = minIndex;
        }
        
        //se intercambia el elemento maximo con el elemento en la posición n - 1 - i
        if (maxIndex != n - 1 - i) {
            temp = arr[n - 1 - i];
            arr[n - 1 - i] = arr[maxIndex];
            arr[maxIndex] = temp;
        }
    }
}