# Makefile para el proyecto principal con cleanrun

# Directorios
INCDIR := incs
SRCDIR := src
OBJDIR := obj

# Compilador y flags
CC     := gcc
CFLAGS := -Wall -Wextra -I$(INCDIR) -g

# Fuentes del proyecto principal (excluye utils en tools/)
SRC := $(filter-out \
        $(SRCDIR)/test_algos.c \
        $(SRCDIR)/generastock.c, \
        $(wildcard $(SRCDIR)/*.c))

# Objetos van a obj/
OBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

# Ejecutable del proyecto principal
TARGET := programa

# Binario de generador de stock
GEN := tools/generastock

.PHONY: all clean cleanrun generastock

all: $(OBJDIR) $(TARGET)

# Crear obj/ si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compilar proyecto principal
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regla genérica .c -> obj/%.o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar objetos y ejecutable
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Compilar y ejecutar generastock
generastock: tools/generastock.c
	$(CC) $(CFLAGS) -o $(GEN) tools/generastock.c

# cleanrun: limpia, compila proyecto, genera CSV y ejecuta programa
cleanrun: clean all generastock
	@echo "\n>>> Generando inventario..."
	@./$(GEN)
	@echo "\n>>> Ejecutando programa principal..."
	@./$(TARGET) docs/inventario.csv