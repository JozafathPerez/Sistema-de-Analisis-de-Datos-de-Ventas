#include "headers.h"

int buscarCategoria(CategoriaTotal *categorias, int totalCategorias, const char *categoria) {
    // Buscar la categoría en el arreglo de categorías
    for (int i = 0; i < totalCategorias; i++) {
        if (strcmp(categorias[i].categoria, categoria) == 0) {
            return i;
        }
    }
    return -1;
}

int compararCategorias(const void *a, const void *b) {
    // Comparar dos categorías por ventas totales
    CategoriaTotal *catA = (CategoriaTotal *)a;
    CategoriaTotal *catB = (CategoriaTotal *)b;
    return (catB->totalVentas > catA->totalVentas) - (catB->totalVentas < catA->totalVentas);
}

void mostrarTop5Categorias(Sale *sales, int totalSales) {
    // Crear un arreglo de estructuras CategoriaTotal para almacenar las ventas por categoría
    CategoriaTotal *categorias = malloc(totalSales * sizeof(CategoriaTotal));
    int totalCategorias = 0;

    if (categorias == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return;
    }

    // Procesar las ventas y acumular las ventas por categoría
    for (int i = 0; i < totalSales; i++) {
        int indexCategoria = buscarCategoria(categorias, totalCategorias, sales[i].categoria);
        if (indexCategoria == -1) {
            if (totalCategorias < totalSales) {
                categorias[totalCategorias].categoria = sales[i].categoria;
                categorias[totalCategorias].totalVentas = sales[i].total;
                totalCategorias++;
            }
        } else {
            categorias[indexCategoria].totalVentas += sales[i].total;
        }
    }

    // Ordenar las categorías por ventas totales
    qsort(categorias, totalCategorias, sizeof(CategoriaTotal), compararCategorias);

    // Imprimir el top 5 de categorías
    printf("\n--- Top 5 Categorias con Mayores Ventas ---\n");
    printf("| %-3s | %-20s | %-15s |\n", "No.", "Categoria", "Total Ventas");
    printf("|-----|----------------------|-----------------|\n");

    for (int i = 0; i < 5 && i < totalCategorias; i++) {
        printf("| %-3d | %-20s | %-15.2f |\n", i + 1, categorias[i].categoria, categorias[i].totalVentas);
    }

    printf("|-----|----------------------|-----------------|\n");

    free(categorias);
}