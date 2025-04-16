#include "test_algos.h"
#include "producto.h"
#include "comparadores.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "busbi.h"
#include "bussec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define INITIAL_CAPACITY 1024
#define LINE_BUFFER      256

//lee CSV y construye un arreglo de producto
static size_t leerCSV(const char *filename, Producto **outArr) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("fopen"); return 0; }
    size_t cap = INITIAL_CAPACITY, cnt = 0;
    Producto *arr = malloc(cap * sizeof *arr);
    if (!arr) { perror("malloc"); fclose(fp); return 0; }

    char line[LINE_BUFFER];
    fgets(line, LINE_BUFFER, fp); //salta encabezado

    while (fgets(line, LINE_BUFFER, fp)) {
        if (cnt >= cap) {
            cap *= 2;
            Producto *tmp = realloc(arr, cap * sizeof *arr);
            if (!tmp) { perror("realloc"); break; }
            arr = tmp;
        }
        char *tok = strtok(line, ",");
        if (!tok) continue;
        arr[cnt].id = atoi(tok);

        tok = strtok(NULL, ","); if (!tok) continue;
        strncpy(arr[cnt].nombre, tok, sizeof arr[cnt].nombre - 1);
        tok = strtok(NULL, ","); if (!tok) continue;
        strncpy(arr[cnt].categoria, tok, sizeof arr[cnt].categoria - 1);
        tok = strtok(NULL, ","); if (!tok) continue;
        arr[cnt].precio = atof(tok);
        tok = strtok(NULL, ",\n"); if (!tok) continue;
        arr[cnt].stock = atoi(tok);

        cnt++;
    }
    fclose(fp);
    *outArr = arr;
    return cnt;
}

//copia un arreglo de producto
static void copyProducts(const Producto *src, Producto *dst, size_t n) {
    memcpy(dst, src, n * sizeof *dst);
}

static int compareInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void test_algorithms(const char *csv_filename) {
    Producto *products = NULL;
    size_t n = leerCSV(csv_filename, &products);
    if (n == 0) {
        fprintf(stderr, "Error leyendo productos.\n");
        return;
    }
    printf("== Pruebas con %zu productos de '%s' ==\n\n", n, csv_filename);

    Producto *temp = malloc(n * sizeof *temp);
    if (!temp) { perror("malloc temp"); free(products); return; }

    //array de criterios de ordenamiento
    struct {
        const char *label;
        ComparadorProducto cmp;
    } criterios[] = {
        { "ID",        compararPorId },
        { "NOMBRE",    compararPorNombre },
        { "CATEGORIA", compararPorCategoria },
        { "PRECIO",    compararPorPrecio },
        { "STOCK",     compararPorStock }
    };
    size_t m = sizeof criterios / sizeof *criterios;

    clock_t start, end;
    double elapsed;

    //para cada algoritmo y cada criterio
    for (size_t c = 0; c < m; c++) {
        //bubble sort
        copyProducts(products, temp, n);
        start = clock();
        bubbleSortProductos(temp, n, criterios[c].cmp);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("BubbleSort por %-9s: %.6f s\n", criterios[c].label, elapsed);
        sleep(1);

        //insertion sort
        copyProducts(products, temp, n);
        start = clock();
        insertionSortProductos(temp, n, criterios[c].cmp);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("InsertionSort por %-9s: %.6f s\n", criterios[c].label, elapsed);
        sleep(1);

        //selection sort
        copyProducts(products, temp, n);
        start = clock();
        selectionSortProductos(temp, n, criterios[c].cmp);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("SelectionSort por %-9s: %.6f s\n\n", criterios[c].label, elapsed);
        sleep(1);
    }

    //pruebas de busqueda valores enteros
    int *vals = malloc(n * sizeof *vals);
    int *valsSorted = malloc(n * sizeof *valsSorted);
    if (!vals || !valsSorted) {
        perror("malloc vals");
        free(temp); free(products);
        return;
    }
    for (size_t i = 0; i < n; i++) vals[i] = products[i].id;
    int key = vals[n-1];

    //busqueda secuencial por id
    start = clock();
    int idxSec = BuscSec(vals, n, key);
    end   = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("BuscSec (ID, key=%d): idx=%d, %.6f s\n", key, idxSec, elapsed);
    sleep(1);

    //busqueda binaria por id
    memcpy(valsSorted, vals, n * sizeof *valsSorted);
    qsort(valsSorted, n, sizeof *valsSorted, compareInt);
    start = clock();
    int idxBin = BusBi(valsSorted, n, key);
    end   = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("BusBi   (ID, key=%d): idx=%d, %.6f s\n\n", key, idxBin, elapsed);
    sleep(1);

    //repetir busquedas con stock
    for (size_t i = 0; i < n; i++) vals[i] = products[i].stock;
    key = vals[n-1];
    start = clock();
    idxSec = BuscSec(vals, n, key);
    end   = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("BuscSec (STOCK, key=%d): idx=%d, %.6f s\n", key, idxSec, elapsed);
    sleep(1);

    memcpy(valsSorted, vals, n * sizeof *valsSorted);
    qsort(valsSorted, n, sizeof *valsSorted, compareInt);
    start = clock();
    idxBin = BusBi(valsSorted, n, key);
    end   = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("BusBi   (STOCK, key=%d): idx=%d, %.6f s\n\n", key, idxBin, elapsed);
    sleep(1);

    //liberar todo
    free(valsSorted);
    free(vals);
    free(temp);
    free(products);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <archivo.csv>\n", argv[0]);
        return 1;
    }
    test_algorithms(argv[1]);
    return 0;
}