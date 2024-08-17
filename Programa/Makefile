# Definir el compilador y las opciones
CC = gcc
CFLAGS = -lm

# Definir los archivos fuente y el ejecutable
SRC = ./src/main.c ./lib/cJSON/cJSON.c
TARGET = main.exe

# Regla principal
all: $(TARGET) run

# Regla para compilar el código
$(TARGET): $(SRC)
    $(CC) $(SRC) -o $(TARGET) $(CFLAGS)

# Regla para ejecutar el archivo compilado
run: $(TARGET)
    @echo Ejecutando $(TARGET)...
    @$(TARGET)

# Regla para limpiar los archivos generados
clean:
    @del $(TARGET)