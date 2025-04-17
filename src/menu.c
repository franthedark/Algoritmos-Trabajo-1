#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "menu.h"
#include "lectorcsv.h"
#include "bubblesort.h"
#include "comparadores.h"
#include "bussec.h"
#include "busbi.h"

#define MAX_PRODUCTOS 1000

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

void mostrarMenu() {
    printf("\n--- Menu del Sistema de Inventario ---\n");
    printf("1. Leer archivo CSV\n");
    printf("2. Ordenar productos por ID\n");
    printf("3. Ordenar productos por precio\n");
    printf("4. Ordenar productos por nombre\n");
    printf("5. Ordenar productos por categoria\n");
    printf("6. Ordenar productos por stock\n");
    printf("7. Buscar producto\n");
    printf("8. Mostrar estadisticas del inventario\n");
    printf("9. Mostrar todos los productos\n");
    printf("10. Salir\n");
    printf("Seleccione una opcion: ");
}

void ejecutarMenu() {
    setlocale(LC_ALL, "");
    Producto productos[MAX_PRODUCTOS];
    int cantidad = 0;
    int opcion;
    int csvcargado = 0;

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        if (!csvcargado && opcion >= 2 && opcion <= 9) {
            printf("Primero debe cargar el archivo CSV (opción 1).\n");
            continue;
        }

        switch (opcion) {
            case 1:
                leerCSV("docs/inventario.csv", productos, &cantidad);
                if (cantidad > 0) {
                    imprimirTablaProductos(productos, cantidad);
                    csvcargado = 1;
                } else {
                    printf("No se cargaron productos.\n");
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

            case 4:
                bubbleSortProductos(productos, cantidad, compararPorNombre);
                printf("Productos ordenados por nombre.\n");
                break;

            case 5:
                bubbleSortProductos(productos, cantidad, compararPorCategoria);
                printf("Productos ordenados por categoría.\n");
                break;

            case 6:
                bubbleSortProductos(productos, cantidad, compararPorStock);
                printf("Productos ordenados por stock.\n");
                break;

            case 7: {
                int subopcion;
                printf("\n--- Opciones de Busqueda ---\n");
                printf("1. Buscar por nombre (secuencial)\n");
                printf("2. Buscar por nombre (binaria)\n");
                printf("3. Buscar por precio (secuencial)\n");
                printf("4. Buscar por precio (binaria)\n");
                printf("5. Buscar por ID (secuencial)\n");
                printf("6. Buscar por ID (binaria)\n");

                printf("Seleccione una opción: ");
                scanf("%d", &subopcion);

                if (subopcion == 1) {
                    char nombreBuscado[50];
                    printf("Ingrese el nombre del producto a buscar: ");
                    getchar(); // Limpia el buffer
                    fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
                    nombreBuscado[strcspn(nombreBuscado, "\n")] = 0;

                    int indice = SecBusxNom(productos, cantidad, nombreBuscado);
                    if (indice != -1) {
                        printf("Producto encontrado: ID=%d | Nombre=%s | Precio=%.2f\n",
                               productos[indice].id, productos[indice].nombre, productos[indice].precio);
                    } else {
                        printf("Producto no encontrado.\n");
                    }
                } else if (subopcion == 2) {
                    char nombreBuscado[50];
                    printf("Ingrese el nombre del producto a buscar: ");
                    getchar();
                    fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
                    nombreBuscado[strcspn(nombreBuscado, "\n")] = 0;

                    int indice = buscarPorNombreBinaria(productos, cantidad, nombreBuscado);
                    if (indice != -1) {
                        printf("Producto encontrado: ID=%d | Nombre=%s | Precio=%.2f\n",
                               productos[indice].id, productos[indice].nombre, productos[indice].precio);
                    } else {
                        printf("Producto no encontrado.\n");
                    }
                } else if (subopcion == 3) {
                    double precioMin, precioMax;
                    printf("Ingrese el precio mínimo: ");
                    scanf("%lf", &precioMin);
                    printf("Ingrese el precio máximo: ");
                    scanf("%lf", &precioMax);

                    SecBuscarRangoPrecio(productos, cantidad, precioMin, precioMax);
                } else if (subopcion == 4) {
                    double precioBuscado;
                    printf("Ingrese el precio del producto a buscar: ");
                    scanf("%lf", &precioBuscado);

                    int indice = buscarPorPrecioBinaria(productos, cantidad, precioBuscado);
                    if (indice != -1) {
                        printf("Producto encontrado: ID=%d | Nombre=%s | Precio=%.2f\n",
                               productos[indice].id, productos[indice].nombre, productos[indice].precio);
                    } else {
                        printf("Producto no encontrado.\n");
                    }
                }else if (subopcion == 5) {
                    int id;
                    printf("Ingrese el ID del producto a buscar: ");
                    scanf("%d", &id);

                    int indice = SecBusxID(productos, cantidad, id);
                    if (indice != -1) {
                        printf("Producto encontrado: ID=%d | Nombre=%s | Precio=%.2f\n",
                            productos[indice].id, productos[indice].nombre, productos[indice].precio);
                    } else {
                        printf("Producto no encontrado.\n");
                    }
                } else if (subopcion == 6) {
                    int id;
                    printf("Ingrese el ID del producto a buscar: ");
                    scanf("%d", &id);

                    int indice = buscarPorIDBinaria(productos, cantidad, id);
                    if (indice != -1) {
                        printf("Producto encontrado: ID=%d | Nombre=%s | Precio=%.2f\n",
                            productos[indice].id, productos[indice].nombre, productos[indice].precio);
                    } else {
                        printf("Producto no encontrado.\n");
                    }
                }

                 else {
                    printf("Opción no valida.\n");
                }
                break;
            }

            case 8: {
                double valorTotal = 0;
                Producto *masCaro = NULL;
                int bajoStock = 0, caros = 0;

                for (int i = 0; i < cantidad; i++) {
                    valorTotal += productos[i].precio * productos[i].stock;

                    if (!masCaro || productos[i].precio > masCaro->precio)
                        masCaro = &productos[i];

                    if (productos[i].stock < 10)
                        bajoStock++;

                    if (productos[i].precio > 200.0)
                        caros++;
                }

                printf("Valor total del inventario: %.2f\n", valorTotal);
                if (masCaro) {
                    printf("Producto mas caro: ID=%d | Nombre=%s | Precio=%.2f\n",
                           masCaro->id, masCaro->nombre, masCaro->precio);
                }
                printf("%% productos con bajo stock: %.2f%%\n", (bajoStock * 100.0) / cantidad);
                printf("%% productos caros (> $200): %.2f%%\n", (caros * 100.0) / cantidad);
                break;
            }

            case 9:
                if (cantidad > 0) {
                    imprimirTablaProductos(productos, cantidad);
                } else {
                    printf("No hay productos cargados.\n");
                }
                break;

            case 10:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }

    } while (opcion != 10);
}
