#include "selectionsort.h"

void selectionSortProductos(Producto arr[], int n) {
    int i, j, minIndex, maxIndex;
    Producto temp;
    for (i = 0; i < n / 2; i++) {
        minIndex = i;
        maxIndex = i;
        //se busca el elemento minimo y maximo en el subarreglo no ordenado
        for (j = i; j < n - i; j++) {
            if (arr[j].precio < arr[minIndex].precio)
                minIndex = j;
            if (arr[j].precio > arr[maxIndex].precio)
                maxIndex = j;
        }
        //se intercambia el elemento minimo con el elemento en la posición i si es necesario
        if (minIndex != i) {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            //si el elemento maximo se encontraba en la posicion i se actualiza su indice
            if (maxIndex == i)
                maxIndex = minIndex;
        }
        //se intercambia el elemento maximo con el elemento en la posicion n - 1 - i
        if (maxIndex != n - 1 - i) {
            temp = arr[n - 1 - i];
            arr[n - 1 - i] = arr[maxIndex];
            arr[maxIndex] = temp;
        }
    }
}
