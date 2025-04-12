#include "insertionsort.h"

//funcion auxiliar que utiliza busqueda binaria para encontrar la posicion de insercion para key en el subarreglo
//se utiliza la funcion comparadora cmp para determinar el orden
static int binarySearch(Producto arr[], int left, int right, Producto key, ComparadorProducto cmp) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (cmp(&arr[mid], &key) <= 0)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void insertionSortProductos(Producto arr[], int n, ComparadorProducto cmp) {
    int i, j, insertIndex;
    Producto key;
    
    //se recorre el arreglo a partir del segundo elemento
    for (i = 1; i < n; i++) {
        key = arr[i];
        //se utiliza busqueda binaria para hallar la posicion de insercion en el subarreglo ordenado
        insertIndex = binarySearch(arr, 0, i, key, cmp);
        
        //se desplazan los elementos para hacer espacio a key
        j = i;
        while (j > insertIndex) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[insertIndex] = key;
    }
}