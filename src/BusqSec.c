#include "bussec.h"

int Bseq2(int v[], int x, int n) {
    int r = 0;
    while (r < n && v[r] != x) {
        if (v[r] > x)  // Si el valor actual es mayor que el valor buscado, terminamos la búsqueda
            break;
        r = r + 1;
    }
    return r;
}


int SecBusxNom(Producto productos[], int n, const char* nombreb) {
    for (int i = 0; i < n; i++) {
        if (strcmp(productos[i].nombre, nombreb) == 0) {
            return i;
        }
    }
    return -1;
}

void SecBuscarRangoPrecio(Producto productos[], int n, double min, double max) {
    for (int i = 0; i < n; i++) {
        if (productos[i].precio >= min && productos[i].precio <= max) {
            printf("Producto encontrado: %s | Precio: %.2f | ID: %d\n",
                   productos[i].nombre, productos[i].precio, productos[i].id);
        }
    }
}

int SecBusxID(Producto productos[], int n, int idBuscado) {
    for (int i = 0; i < n; i++) {
        if (productos[i].id == idBuscado) {
            return i;
        }
    }
    return -1;
}
