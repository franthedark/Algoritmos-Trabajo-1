#include "producto.h"
#include "comparadores.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "bussec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define INITIAL_CAPACITY 1024
#define LINE_BUFFER      256
#define RESULTS_FILE     "docs/resultados.txt"

extern void bubbleSortProductos(Producto arr[], int n, ComparadorProducto cmp);
extern void insertionSortProductos(Producto arr[], int n, ComparadorProducto cmp);
extern void selectionSortProductos(Producto arr[], int n, ComparadorProducto cmp);

static int BusBi(int v[], int n, int x) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (v[mid] == x) return mid;
        if (v[mid] < x)  lo = mid + 1;
        else             hi = mid - 1;
    }
    return -1;
}

static void print_system_info(void) {
    FILE *fp;
    char line[256];
    printf("=== Información del sistema ===\n");

    // CPU
    if ((fp = fopen("/proc/cpuinfo","r"))) {
        int cores = 0; char model[256] = "";
        while (fgets(line,sizeof(line),fp)) {
            if (!strncmp(line,"processor",9)) cores++;
            else if (!strncmp(line,"model name",10) && !model[0]) {
                char *p = strchr(line,':');
                if (p) {
                    strncpy(model,p+2,sizeof(model)-1);
                    model[strcspn(model,"\n")] = 0;
                }
            }
        }
        fclose(fp);
        printf("CPU: %s  (%d cores)\n",model,cores);
    } else perror("Error abriendo /proc/cpuinfo");

    // RAM
    if ((fp = fopen("/proc/meminfo","r"))) {
        long mem_kb = 0;
        while (fgets(line,sizeof(line),fp)) {
            if (!strncmp(line,"MemTotal:",9)) {
                sscanf(line+9,"%ld",&mem_kb);
                break;
            }
        }
        fclose(fp);
        if (mem_kb)
            printf("RAM total: %.2f GB\n", mem_kb/1024.0/1024.0);
    } else perror("Error abriendo /proc/meminfo");

    printf("================================\n\n");
}

static size_t leerCSV(const char *file, Producto **out) {
    FILE *fp = fopen(file,"r");
    if (!fp) { perror("fopen"); return 0; }

    size_t cap = INITIAL_CAPACITY, cnt = 0;
    Producto *arr = malloc(cap * sizeof *arr);
    if (!arr) { perror("malloc"); fclose(fp); return 0; }

    char line[LINE_BUFFER];
    // saltar encabezado
    if (!fgets(line,sizeof(line),fp)) {
        fclose(fp); free(arr); return 0;
    }

    while (fgets(line,sizeof(line),fp)) {
        if (cnt >= cap) {
            cap *= 2;
            Producto *tmp = realloc(arr, cap * sizeof *tmp);
            if (!tmp) { perror("realloc"); break; }
            arr = tmp;
        }
        char *tok = strtok(line,",");
        if (!tok) continue;
        arr[cnt].id = atoi(tok);

        tok = strtok(NULL,","); if (!tok) continue;
        strncpy(arr[cnt].nombre, tok, sizeof arr[cnt].nombre - 1);

        tok = strtok(NULL,","); if (!tok) continue;
        strncpy(arr[cnt].categoria, tok, sizeof arr[cnt].categoria - 1);

        tok = strtok(NULL,","); if (!tok) continue;
        arr[cnt].precio = atof(tok);

        tok = strtok(NULL,",\n"); if (!tok) continue;
        arr[cnt].stock = atoi(tok);

        cnt++;
    }

    fclose(fp);
    *out = arr;
    return cnt;
}

static void copyProds(const Producto *src, Producto *dst, size_t n) {
    memcpy(dst, src, n * sizeof *dst);
}

static int compareInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

typedef struct { char name[32]; double time; } Result;
static int cmpRes(const void *a, const void *b) {
    double ta = ((Result*)a)->time, tb = ((Result*)b)->time;
    return ta < tb ? -1 : ta > tb ? 1 : 0;
}

// Función para graficar usando gnuplot (gráfico de línea)
static void plotResults(const Result results[], int rc) {
    FILE *gp = popen("gnuplot -persist", "w");
    if (!gp) {
        perror("popen gnuplot");
        return;
    }
    fprintf(gp,
        "set title 'Rendimiento de Algoritmos'\n"
        "set ylabel 'Tiempo (s)'\n"
        "set style data linespoints\n"
        "set xtics rotate by -45 scale 0\n"
        "plot '-' using 2:xtic(1) with linespoints notitle\n"
    );
    for (int i = 0; i < rc; i++) {
        fprintf(gp, "\"%s\" %.15f\n", results[i].name, results[i].time);
    }
    fprintf(gp, "e\n");
    pclose(gp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr,"Uso: %s <archivo.csv>\n",argv[0]);
        return EXIT_FAILURE;
    }
    print_system_info();

    Producto *prods = NULL;
    size_t n = leerCSV(argv[1], &prods);
    if (!n) {
        fprintf(stderr,"Error leyendo %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    Result results[7]; int rc = 0;

    FILE *out = fopen(RESULTS_FILE,"w");
    if (!out) { perror("fopen resultados"); free(prods); return EXIT_FAILURE; }
    fprintf(out,"=== Resultados (%zu productos) ===\n\n", n);

    Producto *tmp = malloc(n * sizeof *tmp);
    if (!tmp) { perror("malloc tmp"); fclose(out); free(prods); return EXIT_FAILURE; }

    clock_t t0; double dt;

    // ordenación por precio ---
    copyProds(prods, tmp, n);
    t0 = clock();
    bubbleSortProductos(tmp, n, compararPorPrecio);
    dt = (double)(clock() - t0) / CLOCKS_PER_SEC;
    snprintf(results[rc].name,32,"BubbleSort PRICE"); results[rc++].time = dt;
    fprintf(out,"%-20s: %.15f s\n","BubbleSort PRICE", dt);

    copyProds(prods, tmp, n);
    t0 = clock();
    insertionSortProductos(tmp, n, compararPorPrecio);
    dt = (double)(clock() - t0) / CLOCKS_PER_SEC;
    snprintf(results[rc].name,32,"InsertionSort PRICE"); results[rc++].time = dt;
    fprintf(out,"%-20s: %.15f s\n","InsertionSort PRICE", dt);

    copyProds(prods, tmp, n);
    t0 = clock();
    selectionSortProductos(tmp, n, compararPorPrecio);
    dt = (double)(clock() - t0) / CLOCKS_PER_SEC;
    snprintf(results[rc].name,32,"SelectionSort PRICE"); results[rc++].time = dt;
    fprintf(out,"%-20s: %.15f s\n\n","SelectionSort PRICE", dt);

    // busqueda secuencial y binaria por id y stock
    int *vals   = malloc(n * sizeof *vals);
    int *sorted = malloc(n * sizeof *sorted);
    int idx, key;

    // id
    for (size_t i = 0; i < n; i++) vals[i] = prods[i].id;
    key = vals[n - 1];
    t0 = clock();
    idx = Bseq2(vals, key, (int)n);
    dt = (double)(clock() - t0) / CLOCKS_PER_SEC;
    snprintf(results[rc].name,32,"Bseq2 ID"); results[rc++].time = dt;
    fprintf(out,"%-20s idx=%d, %.15f s\n","Bseq2 ID", idx, dt);

    memcpy(sorted, vals, n * sizeof *sorted);
    qsort(sorted, n, sizeof *sorted, compareInt);
    t0 = clock();
    idx = BusBi(sorted, (int)n, key);
    dt = (double)(clock() - t0) / CLOCKS_PER_SEC;
    snprintf(results[rc].name,32,"BusBi ID"); results[rc++].time = dt;
    fprintf(out,"%-20s idx=%d, %.15f s\n\n","BusBi ID", idx, dt);

    // stock
    for (size_t i = 0; i < n; i++) vals[i] = prods[i].stock;
    key = vals[n - 1];
    t0 = clock();
    idx = Bseq2(vals, key, (int)n);
    dt = (double)(clock() - t0) / CLOCKS_PER_SEC;
    snprintf(results[rc].name,32,"Bseq2 STOCK"); results[rc++].time = dt;
    fprintf(out,"%-20s idx=%d, %.15f s\n","Bseq2 STOCK", idx, dt);

    memcpy(sorted, vals, n * sizeof *sorted);
    qsort(sorted, n, sizeof *sorted, compareInt);
    t0 = clock();
    idx = BusBi(sorted, (int)n, key);
    dt = (double)(clock() - t0) / CLOCKS_PER_SEC;
    snprintf(results[rc].name,32,"BusBi STOCK"); results[rc++].time = dt;
    fprintf(out,"%-20s idx=%d, %.15f s\n\n","BusBi STOCK", idx, dt);

    // ranking final
    fprintf(out,"=== Ranking ascendente ===\n");
    qsort(results, rc, sizeof results[0], cmpRes);
    for (int i = 0; i < rc; i++) {
        fprintf(out,"%2d) %-20s: %.15f s\n",
                i+1, results[i].name, results[i].time);
    }

    fclose(out);

    // Graficar resultados
    plotResults(results, rc);

    // limpieza
    free(tmp);
    free(prods);
    free(vals);
    free(sorted);

    return EXIT_SUCCESS;
}