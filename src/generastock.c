#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINEA     100
#define MAX_PALABRAS  3000
#define MAX_NOMBRE    100
#define ARCHIVO_PALABRAS "../docs/palabras.txt"
#define ARCHIVO_SALIDA   "../docs/inventario.csv"

//verifica si un id ya fue utilizado
int id_repetido(int *ids, int cantidad, int nuevo_id) {
    for (int i = 0; i < cantidad; i++) {
        if (ids[i] == nuevo_id) return 1;
    }
    return 0;
}

int main() {
    int cantidad;
    FILE *archivo_csv, *archivo_txt;
    char *palabras[MAX_PALABRAS];
    int total_palabras = 0;
    int *ids_usados;

    srand((unsigned)time(NULL));

    //leer palabras desde el archivo
    archivo_txt = fopen(ARCHIVO_PALABRAS, "r");
    if (!archivo_txt) {
        perror("Error al abrir palabras.txt");
        return 1;
    }

    char linea[MAX_LINEA];
    while (fgets(linea, sizeof(linea), archivo_txt) && total_palabras < MAX_PALABRAS) {
        linea[strcspn(linea, "\n")] = 0;
        palabras[total_palabras] = strdup(linea);
        total_palabras++;
    }
    fclose(archivo_txt);

    if (total_palabras == 0) {
        fprintf(stderr, "No se encontraron palabras clave en el archivo.\n");
        return 1;
    }

    printf("Ingrese la cantidad de productos a generar: ");
    if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
        fprintf(stderr, "Cantidad inválida.\n");
        return 1;
    }

    ids_usados = malloc(sizeof(int) * cantidad);
    if (!ids_usados) {
        perror("Error al reservar memoria para IDs");
        return 1;
    }

    archivo_csv = fopen(ARCHIVO_SALIDA, "w");
    if (!archivo_csv) {
        perror("Error al crear archivo CSV");
        free(ids_usados);
        return 1;
    }

    //encabezado csv
    fprintf(archivo_csv, "id,nombre,categoria,precio,stock\n");

    for (int i = 0; i < cantidad; i++) {
        int id_aleatorio;
        //generar id unico
        do {
            id_aleatorio = rand() % (cantidad * 10) + 1;
        } while (id_repetido(ids_usados, i, id_aleatorio));
        ids_usados[i] = id_aleatorio;

        //elegir palabra base y numero de modelo
        int idx_pal = rand() % total_palabras;
        int modelo_num = rand() % 500 + 1;

        //construye nombre y reemplaza espacios por guiones bajos
        char nombre[MAX_NOMBRE];
        snprintf(nombre, MAX_NOMBRE, "%s_%d", palabras[idx_pal], modelo_num);

        //precio y stock aleatorios
        float precio = (rand() % 5000000 + 10000) / 100.0f;
        int stock   = rand() % 100 + 1;

        fprintf(archivo_csv, "%d,%s,%s,%.2f,%d\n",
                id_aleatorio,
                nombre,
                palabras[idx_pal],
                precio,
                stock);
    }

    fclose(archivo_csv);
    free(ids_usados);
    for (int i = 0; i < total_palabras; i++)
        free(palabras[i]);

    printf("Archivo %s generado correctamente con %d productos.\n",
           ARCHIVO_SALIDA, cantidad);
    return 0;
}