#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lectorcsv.h"
#include "bubblesort.h"
#include "comparadores.h"
#include "bussec.h"
#include "time.h"
#include <locale.h> // Necesario para setlocale

#define MAX_PRODUCTOS 1000

void imprimirTablaProductos(Producto productos[], int cantidad);

void mostrarMenu() {
    printf("\n--- Menu del Sistema de Inventario ---\n");
    printf("1. Leer archivo CSV\n");
    printf("2. Ordenar productos por ID\n");
    printf("3. Ordenar productos por precio\n");
    printf("4. Buscar producto por nombre\n");
    printf("5. Mostrar estadisticas del inventario\n");
    printf("6. Generar productos aleatorios\n"); // Nueva opción
    printf("7. Mostrar todos los productos\n");
    printf("8. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    setlocale(LC_ALL, ""); // Configura la codificación según el sistema
    Producto productos[MAX_PRODUCTOS];
    int cantidad = 0;
    int opcion;

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                leerCSV("../docs/inventario.csv", productos, &cantidad);
                if (cantidad > 0) {
                    imprimirTablaProductos(productos, cantidad);
                }
                break;
            case 2:
                bubbleSortProductos(productos, cantidad, compararPorId);
                printf("Productos ordenados por ID.\n");
                break;
            case 3:
                bubbleSortProductos(productos, cantidad, compararPorPrecio);
                printf("Productos ordenados por precio.\n");
                break;
            case 4: {
                char nombreBuscado[50];
                printf("Ingrese el nombre del producto a buscar: ");
                getchar(); // Limpia el buffer de entrada
                fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
                nombreBuscado[strcspn(nombreBuscado, "\n")] = 0; // Elimina el salto de línea

                int indice = SecBusxNom(productos, cantidad, nombreBuscado);
                if (indice != -1) {
                    printf("Producto encontrado: ID=%d, Nombre=%s, Precio=%.2f\n",
                           productos[indice].id, productos[indice].nombre, productos[indice].precio);
                } else {
                    printf("Producto no encontrado.\n");
                }
                break;
            }
            case 5: {
                double valorTotal = 0;
                Producto *masCaro = NULL;
                int productosBajoStock = 0;
                int productosCaros = 0;

                for (int i = 0; i < cantidad; i++) {
                    // Asegúrate de usar el precio y el stock correctamente
                    valorTotal += productos[i].precio * productos[i].stock;

                    if (masCaro == NULL || productos[i].precio > masCaro->precio) {
                        masCaro = &productos[i];
                    }
                    if (productos[i].stock < 10) {
                        productosBajoStock++;
                    }
                    if (productos[i].precio > 200.00) {
                        productosCaros++;
                    }
                }

                printf("Valor total del inventario: %.2f\n", valorTotal);
                if (masCaro) {
                    printf("Producto más caro: ID=%d, Nombre=%s, Precio=%.2f\n",
                           masCaro->id, masCaro->nombre, masCaro->precio);
                }
                printf("Porcentaje de productos con stock bajo: %.2f%%\n",
                       (productosBajoStock * 100.0) / cantidad);
                printf("Porcentaje de productos caros: %.2f%%\n",
                       (productosCaros * 100.0) / cantidad);
                break;
            }
            case 6: {
                int cantidad;
                printf("Ingrese la cantidad de productos a generar: ");
                scanf("%d", &cantidad);

                FILE *archivo_txt = fopen("../docs/palabras.txt", "r");
                if (!archivo_txt) {
                    perror("Error al abrir palabras.txt");
                    break;
                }

                char *palabras[MAX_PRODUCTOS];
                int total_palabras = 0;
                char linea[100];

                // Leer palabras desde el archivo
                while (fgets(linea, sizeof(linea), archivo_txt) && total_palabras < MAX_PRODUCTOS) {
                    linea[strcspn(linea, "\n")] = 0; // Eliminar el salto de línea
                    palabras[total_palabras] = strdup(linea);
                    total_palabras++;
                }
                fclose(archivo_txt);

                if (total_palabras == 0) {
                    printf("No se encontraron palabras en el archivo.\n");
                    break;
                }

                FILE *archivo_csv = fopen("../docs/inventario.csv", "w");
                if (!archivo_csv) {
                    perror("Error al crear el archivo CSV");
                    break;
                }

                fprintf(archivo_csv, "id,nombre,categoria,precio,stock\n");

                srand(time(NULL));
                for (int i = 0; i < cantidad; i++) {
                    int id = rand() % 1000 + 1;
                    int palabra_idx = rand() % total_palabras;
                    int modelo_num = rand() % 500 + 1;

                    char nombre[100];
                    snprintf(nombre, sizeof(nombre), "%s %d", palabras[palabra_idx], modelo_num);

                    char categoria[30];
                    snprintf(categoria, sizeof(categoria), "Categoria %d", rand() % 10 + 1);

                    double precio = (rand() % 10000) / 100.0;
                    int stock = rand() % 100 + 1;

                    fprintf(archivo_csv, "%d,%s,%s,%.2f,%d\n", id, nombre, categoria, precio, stock);
                }

                fclose(archivo_csv);

                // Liberar memoria de las palabras
                for (int i = 0; i < total_palabras; i++) {
                    free(palabras[i]);
                }

                printf("Archivo 'inventario.csv' generado correctamente con %d productos.\n", cantidad);
                break;
            }
            case 7:
                if (cantidad > 0) {
                    imprimirTablaProductos(productos, cantidad);
                } else {
                    printf("No hay productos cargados.\n");
                }
                break;
            case 8:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 8);

    return 0;
}