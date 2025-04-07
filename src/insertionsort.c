#include "insertionsort.h"

static int binarySearch(Producto arr[], int left, int right, double keyPrecio) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].precio <= keyPrecio)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void insertionSortProductos(Producto arr[], int n) {
    int i, j, insertIndex;
    Producto key;
    
    //se recorre el arreglo a partir del segundo elemento
    for (i = 1; i < n; i++) {
        key = arr[i];
        //hallar la posicion de inserción en el subarreglo ya ordenado
        insertIndex = binarySearch(arr, 0, i, key.precio);
        j = i;
        while (j > insertIndex) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[insertIndex] = key;
    }
}