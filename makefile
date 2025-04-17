#makefile para el proyecto principal

#directorios
INCDIR := incs
SRCDIR := src
OBJDIR := obj

#compilador y flags
CC     := gcc
CFLAGS := -Wall -Wextra -I$(INCDIR) -g

SRC := $(filter-out \
        $(SRCDIR)/test_algos.c \
        $(SRCDIR)/generastock.c, \
        $(wildcard $(SRCDIR)/*.c))

#objetos van en obj/, mismo nombre de archivo .o
OBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

#ejecutable
TARGET := programa

.PHONY: all clean cleanrun

#default: crea obj/ y luego el ejecutable
all: $(OBJDIR) $(TARGET)

#crea el directorio obj/ si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

#enlaza el ejecutable a partir de los objetos
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

#limpia objetos y ejecutable
clean:
	rm -rf $(OBJDIR) $(TARGET)

#limpia recompila y ejecuta CSV
cleanrun: clean all
	@./$(TARGET) docs/inventario.csv