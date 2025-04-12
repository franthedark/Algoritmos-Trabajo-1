#ifndef MEMORY_CONTROL_H
#define MEMORY_CONTROL_H

#include <stdlib.h>
#include <stdio.h>

void *mc_malloc(size_t size, const char *file, int line);
void *mc_calloc(size_t nmemb, size_t size, const char *file, int line);
void *mc_realloc(void *ptr, size_t size, const char *file, int line);
void mc_free(void *ptr, const char *file, int line);
void mc_reportLeaks(void);

//macros para facilitar el uso y capturar el archivo y linea automaticamente
#define MALLOC(size) mc_malloc(size, __FILE__, __LINE__)
#define CALLOC(nmemb, size) mc_calloc(nmemb, size, __FILE__, __LINE__)
#define REALLOC(ptr, size) mc_realloc(ptr, size, __FILE__, __LINE__)
#define FREE(ptr) mc_free(ptr, __FILE__, __LINE__)

#endif