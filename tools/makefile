# tools/Makefile

# Directorio de headers del proyecto principal
INCDIR = ../incs

# Flags de compilación
CFLAGS = -Wall -Wextra -I$(INCDIR) -g

.PHONY: all clean cleanrun

# Compila ambas herramientas
all: generastock test_algos

# Generador de CSV
generastock: generastock.c
	gcc $(CFLAGS) -o $@ $<

# Test harness de algoritmos
test_algos: test_algos.c
	gcc $(CFLAGS) -o $@ $< \
	    ../src/bubblesort.c ../src/insertionsort.c ../src/selectionsort.c \
	    ../src/comparadores.c ../src/BusqSec.c

# Limpia ejecutables
clean:
	rm -f generastock test_algos

# Limpia, recompila, genera el inventario y corre las pruebas
cleanrun: clean all
	@echo ">>> Generando inventario..."
	@./generastock
	@echo ">>> Ejecutando pruebas..."
	@cd .. && tools/test_algos docs/inventario.csv