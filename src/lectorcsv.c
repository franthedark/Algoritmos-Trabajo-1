#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "producto.h"

#define MAX_PRODUCTOS 1000

void leerCSV(const char *nombreArchivo, Producto productos[], int *cantidad) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo '%s'.\n", nombreArchivo);
        return;
    }

    char linea[150];
    *cantidad = 0;

    // ignora la primera linea (encabezado)
    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo)) {
        if (*cantidad >= MAX_PRODUCTOS) {
            printf("Advertencia: Se alcanzó el límite máximo de productos (%d).\n", MAX_PRODUCTOS);
            break;
        }
        Producto p;
        if (sscanf(linea, "%d,%49[^,],%29[^,],%lf,%d", 
                   &p.id, p.nombre, p.categoria, &p.precio, &p.stock) != 5) {
            printf("Advertencia: Formato incorrecto en la línea: %s", linea);
            continue;
        }
        productos[*cantidad] = p;
        (*cantidad)++;
    }

    fclose(archivo);
    printf("Archivo '%s' cargado correctamente: %d productos.\n", nombreArchivo, *cantidad);
}


