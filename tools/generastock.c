// tools/generastock.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINEA     100
#define MAX_PALABRAS  3000
#define MAX_NOMBRE    100

// Usamos rutas relativas desde tools/ hacia docs/ en la raíz
#define ARCHIVO_PALABRAS "../docs/palabras.txt"
#define ARCHIVO_SALIDA   "../docs/inventario.csv"

// Verifica si un id ya fue utilizado
static int id_repetido(int *ids, int cantidad, int nuevo_id) {
    for (int i = 0; i < cantidad; i++) {
        if (ids[i] == nuevo_id) return 1;
    }
    return 0;
}

int main(void) {
    int cantidad;
    FILE *archivo_txt = NULL;
    FILE *archivo_csv = NULL;
    char *palabras[MAX_PALABRAS];
    int total_palabras = 0;
    int *ids_usados = NULL;

    srand((unsigned)time(NULL));

    // 1) Abrir el archivo de palabras
    archivo_txt = fopen(ARCHIVO_PALABRAS, "r");
    if (!archivo_txt) {
        fprintf(stderr, "Error al abrir %s\n", ARCHIVO_PALABRAS);
        return 1;
    }

    // 2) Leer todas las líneas (palabras clave)
    {
        char linea[MAX_LINEA];
        while (fgets(linea, sizeof(linea), archivo_txt) && total_palabras < MAX_PALABRAS) {
            linea[strcspn(linea, "\n")] = '\0';
            palabras[total_palabras++] = strdup(linea);
        }
        fclose(archivo_txt);
        if (total_palabras == 0) {
            fprintf(stderr, "No se encontraron palabras en %s\n", ARCHIVO_PALABRAS);
            return 1;
        }
    }

    // 3) Pedir cantidad al usuario
    printf("Ingrese la cantidad de productos a generar: ");
    if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
        fprintf(stderr, "Cantidad inválida.\n");
        // Liberar palabras
        for (int i = 0; i < total_palabras; i++) free(palabras[i]);
        return 1;
    }

    // 4) Reservar arreglo de IDs usados
    ids_usados = malloc(cantidad * sizeof *ids_usados);
    if (!ids_usados) {
        perror("malloc");
        for (int i = 0; i < total_palabras; i++) free(palabras[i]);
        return 1;
    }

    // 5) Abrir CSV de salida
    archivo_csv = fopen(ARCHIVO_SALIDA, "w");
    if (!archivo_csv) {
        fprintf(stderr, "Error al crear %s\n", ARCHIVO_SALIDA);
        free(ids_usados);
        for (int i = 0; i < total_palabras; i++) free(palabras[i]);
        return 1;
    }

    // 6) Escribir encabezado
    fprintf(archivo_csv, "id,nombre,categoria,precio,stock\n");

    // 7) Generar productos
    for (int i = 0; i < cantidad; i++) {
        int id_aleatorio;
        // ID único
        do {
            id_aleatorio = rand() % (cantidad * 10) + 1;
        } while (id_repetido(ids_usados, i, id_aleatorio));
        ids_usados[i] = id_aleatorio;

        // Nombre: palabra + número de modelo
        int idx_pal = rand() % total_palabras;
        int modelo_num = rand() % 500 + 1;
        char nombre[MAX_NOMBRE];
        // reemplazamos espacios por guiones bajos
        snprintf(nombre, sizeof(nombre), "%s_%d", palabras[idx_pal], modelo_num);

        // Precio y stock aleatorios
        float precio = (rand() % 5000000 + 10000) / 100.0f;
        int stock = rand() % 100 + 1;

        // Escribir línea en CSV
        fprintf(archivo_csv, "%d,%s,%s,%.2f,%d\n",
                id_aleatorio,
                nombre,
                palabras[idx_pal],
                precio,
                stock);
    }

    // 8) Cerrar y liberar memoria
    fclose(archivo_csv);
    free(ids_usados);
    for (int i = 0; i < total_palabras; i++) free(palabras[i]);

    printf("Archivo %s generado correctamente con %d productos.\n",
           ARCHIVO_SALIDA, cantidad);
    return 0;
}