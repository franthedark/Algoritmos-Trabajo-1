#include "memory_control.h"
#include <string.h>

//estructura para almacenar informacion de cada asignacion
typedef struct MemoryNode {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct MemoryNode *next;
} MemoryNode;

//puntero global a la lista de asignaciones
static MemoryNode *head = NULL;

//funcion auxiliar para agregar un nodo a la lista
static void add_node(void *ptr, size_t size, const char *file, int line) {
    MemoryNode *node = (MemoryNode *)malloc(sizeof(MemoryNode));
    if (!node) {
        fprintf(stderr, "Error al asignar memoria para el registro de control en %s:%d\n", file, line);
        return;
    }
    node->ptr = ptr;
    node->size = size;
    node->file = file;
    node->line = line;
    node->next = head;
    head = node;
}

//funcion auxiliar para remover un nodo de la lista
static void remove_node(void *ptr) {
    MemoryNode *current = head;
    MemoryNode *prev = NULL;
    while (current != NULL) {
        if (current->ptr == ptr) {
            if (prev)
                prev->next = current->next;
            else
                head = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    fprintf(stderr, "Advertencia: Intento de liberar un puntero no registrado.\n");
}

void *mc_malloc(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (ptr) {
        add_node(ptr, size, file, line);
    } else {
        fprintf(stderr, "Fallo en malloc de %zu bytes en %s:%d\n", size, file, line);
    }
    return ptr;
}

void *mc_calloc(size_t nmemb, size_t size, const char *file, int line) {
    void *ptr = calloc(nmemb, size);
    if (ptr) {
        add_node(ptr, nmemb * size, file, line);
    } else {
        fprintf(stderr, "Fallo en calloc de %zu bytes en %s:%d\n", nmemb * size, file, line);
    }
    return ptr;
}

void *mc_realloc(void *ptr, size_t size, const char *file, int line) {
    if (ptr == NULL) {
        //si ptr es NULL se comporta como malloc
        return mc_malloc(size, file, line);
    }
    //remueve el registro previo
    remove_node(ptr);
    void *new_ptr = realloc(ptr, size);
    if (new_ptr) {
        add_node(new_ptr, size, file, line);
    } else {
        fprintf(stderr, "Fallo en realloc de %zu bytes en %s:%d\n", size, file, line);
    }
    return new_ptr;
}

void mc_free(void *ptr, const char *file, int line) {
    if (ptr == NULL)
        return;
    //se libera la memoria y se remueve el registro
    remove_node(ptr);
    free(ptr);
}

void mc_reportLeaks(void) {
    MemoryNode *current = head;
    if (!current) {
        printf("No se detectaron fugas de memoria.\n");
        return;
    }
    printf("Se detectaron fugas de memoria:\n");
    while (current != NULL) {
        printf("Fuga: %zu bytes asignados en %s:%d no liberados (direccion: %p)\n",
               current->size, current->file, current->line, current->ptr);
        current = current->next;
    }
}