#include "busbi.h"


int binarySearchRec ( int X [] , int l , int r , int key ){
if (l > r)
return -1;
else
{
int mid = l + (r - l) / 2;
if (X[ mid ] == key )
return mid ;
if (X[ mid ] > key )
return binarySearchRec (X , l , mid - 1, key );
else
return binarySearchRec (X , mid + 1, r , key );
}
}


int binarySearchIt ( int X [] , int l , int r , int key ){
while (l <= r ){
int mid = l + (r - l) / 2;
if (X[ mid ] == key )
return mid ;
if (X[ mid ] < key )
l = mid + 1;
else
r = mid - 1;
}
return -1;
}
int buscarPorNombreBinaria(Producto productos[], int n, const char* nombreBuscado) {
    int izquierda = 0, derecha = n - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        int cmp = strcmp(productos[medio].nombre, nombreBuscado);
        if (cmp == 0)
            return medio;
        else if (cmp < 0)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }
    return -1;
}


int buscarPorPrecioBinaria(Producto productos[], int n, double precioBuscado) {
    int izquierda = 0, derecha = n - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (productos[medio].precio == precioBuscado)
            return medio;
        else if (productos[medio].precio < precioBuscado)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }
    return -1;
}


int buscarPorIDBinaria(Producto productos[], int n, int idBuscado) {
    int izquierda = 0, derecha = n - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (productos[medio].id == idBuscado)
            return medio;
        else if (productos[medio].id < idBuscado)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }
    return -1;
}