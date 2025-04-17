#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "producto.h"

#define MAX_LINEA 256
#define MAX_PRODUCTOS 1000

void leerCSV(const char *nombreArchivo, Producto productos[], int *cantidad) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo '%s'.\n", nombreArchivo);
        return;
    }

    char linea[MAX_LINEA];
    *cantidad = 0;

    // Leer y descartar la primera línea (encabezado)
    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo)) {
        if (*cantidad >= MAX_PRODUCTOS) {
            printf("Límite máximo de productos alcanzado (%d).\n", MAX_PRODUCTOS);
            break;
        }

        // Eliminar el salto de línea al final si existe
        linea[strcspn(linea, "\n")] = '\0';

        // Separar la línea en tokens
        char *token = strtok(linea, ",");
        if (!token) continue;
        Producto p;

        // ID
        p.id = atoi(token);

        // Nombre
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(p.nombre, token, sizeof(p.nombre));
        p.nombre[sizeof(p.nombre) - 1] = '\0';

        // Categoría
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(p.categoria, token, sizeof(p.categoria));
        p.categoria[sizeof(p.categoria) - 1] = '\0';

        // Precio
        token = strtok(NULL, ",");
        if (!token) continue;
        p.precio = atof(token);

        // Stock
        token = strtok(NULL, ",");
        if (!token) continue;
        p.stock = atoi(token);

        productos[*cantidad] = p;
        (*cantidad)++;
    }

    fclose(archivo);
    printf("Archivo '%s' cargado correctamente: %d productos.\n", nombreArchivo, *cantidad);
}