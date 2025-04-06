#include "bussec.h"

int bseq2(int v[], int x, int n) {
    int r = 0;
    while (r < n && v[r] != x) {
        if (v[r] > x)  // Si el valor actual es mayor que el valor buscado, terminamos la búsqueda
            break;
        r = r + 1;
    }
    return r;
}
