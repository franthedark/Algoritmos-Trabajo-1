#include "bubblesort.h"

void bubblesortoptimizado(int arr[], int n) {
    int i, newN;
    bool swapped;

    do {
        swapped = false;
        newN = 0;

        for (i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                //intercambia elementos
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;

                swapped = true;
                newN = i;  //ultima posicion swap
            }
        }

        n = newN; //actualiza rango busqueda
    } while (swapped);
}