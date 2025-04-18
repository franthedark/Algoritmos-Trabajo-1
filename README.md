# Algoritmos Trabajo 1
En este proyecto, los estudiantes implementarán y analizarán algoritmos básicos de ordenación y búsqueda, aplicándolos a un sistema de gestión de inventario. El objetivo es desarrollar un sistema que permita ordenar y buscar productos según diferentes criterios, evaluando el rendimiento de los algoritmos implementados.

# Instrucciones para ejecutar el programa y herramientas adicionales

Herramientas extra:

  Si desea ejecutar pruebas y además generar nuevas cantidades siga las siguientes instrucciones:

  1. Diríjase a la carpeta "tools" en la raíz del proyecto.
  2. Ejecute el comando

    make cleanrun

  3. Siga las instrucciones del programa.


  Si desea ejecutar solo el generador de inventario, haga lo siguiente:

  1. Diríjase a la carpeta "tools" en la raíz del proyecto.
  2. Ejecute los siguientes comandos:

    gcc generastock.c -o generar
    ./generar
  
  4. Siga las instrucciones del programa.

Programa Principal:

  1. Diríjase a la carpeta raíz del proyecto.
  2. Ejecute el siguiente comando:

    make cleanrun

  3. Siga las instrucciones del programa.


# Planificación de Roles - Proyecto Sistema de Inventario

# Francisco Mercado

Encargado de Algoritmos de Ordenación y parte del Informe

Responsabilidades principales:
- Implementar:
 * Bubble Sort (con optimizaciones)
 * Selection Sort (in-place)
 * Insertion Sort (optimizado para arrays casi ordenados)
- Redactar parte del informe sobre:
 * Implementación de ordenamientos
 * Análisis teórico de complejidad
 * Comparación experimental de tiempos de ejecución
- Fecha límite para funciones listas: 10 de abril.
  
# Francisco Miranda

Encargado de Algoritmos de Búsqueda y parte del Informe

Responsabilidades principales:

- Implementar:
 * Búsqueda secuencial (básica y optimizada)
 * Búsqueda binaria (iterativa y recursiva)
- Apoyar con funciones de búsqueda por nombre o rango de precios
- Redactar parte del informe sobre:
 * Análisis de búsqueda y rendimiento
 * Comparaciones empíricas entre métodos
- Fecha límite para funciones listas: 10 de abril.
  
# Manuel González

Encargado del Sistema de Inventario, Interfaz y Estadísticas
Responsabilidades principales:

- Crear:
 * Estructura para los productos
 * Lectura del archivo CSV
 * Funciones de ordenamiento/búsqueda integradas al sistema
 * Menú en línea de comandos
 * Estadísticas del inventario (valor total, producto más caro, etc.)
- Redactar parte del informe sobre:
 * Descripción del sistema
 * Capturas de pantalla o flujo de uso
 * Discusión de resultados y mejoras posibles
- Fecha límite para sistema base: 13 de abril.
