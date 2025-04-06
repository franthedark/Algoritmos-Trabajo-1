#include <stdio.h>
#include "bubblesort.h"
#include "bussec.h"
#include "busbi.h" 

int main() {
    int arreglo[] = {5, 3, 8, 4, 2};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);

    bubblesortoptimizado(arreglo, n);

    printf("Arreglo ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");

    //búsqueda binaria iterativa
    int valor = 7;  // Valor a buscar
    int index = binarySearchIt(arreglo, 0, n - 1, valor);
    if (index != -1) {
        printf("Valor %d encontrado en la posición %d (búsqueda iterativa).\n", valor, index);
    } else {
        printf("Valor %d no encontrado (búsqueda iterativa).\n", valor);
    }

    //búsqueda binaria recursiva
    index = binarySearchRec(arreglo, 0, n - 1, valor);
    if (index != -1) {
        printf("Valor %d encontrado en la posición %d (búsqueda recursiva).\n", valor, index);
    } else {
        printf("Valor %d no encontrado (búsqueda recursiva).\n", valor);
    }

    
    

    int buscada = 8;
    int resultado = bseq2(arreglo, buscada, n);

    if (resultado < n) {
        printf("Valor '%d' encontrada en la posición %d.\n", buscada, resultado);
    } else {
        printf("Valor '%d' no encontrada.\n", buscada);
    }

    return 0;
}