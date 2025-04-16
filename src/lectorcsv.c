#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "producto.h"

#define MAX_PRODUCTOS 1000  // Ajustar según necesidad

void leerCSV(const char *nombreArchivo, Producto productos[], int *cantidad) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo '%s'.\n", nombreArchivo);
        return;
    }

    char linea[150];
    *cantidad = 0;

    // Ignorar la primera línea (encabezado)
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

void imprimirTablaProductos(Producto productos[], int cantidad) {
    printf("\n%-10s %-30s %-20s %-10s %-10s\n", "ID", "Nombre", "Categoría", "Precio", "Stock");
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%-10d %-30s %-20s %-10.2f %-10d\n",
               productos[i].id,
               productos[i].nombre,
               productos[i].categoria,
               productos[i].precio,
               productos[i].stock);
    }
}
