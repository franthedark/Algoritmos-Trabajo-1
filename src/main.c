#include <stdio.h>
#include "bubblesort.h"

int main() {
    int arreglo[] = {5, 3, 8, 4, 2};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);

    bubblesortoptimizado(arreglo, n);

    printf("Arreglo ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");

    return 0;
}