#include "headers.h"

void eliminarDuplicados(Sale *sales, int *totalSales) {
    int n = *totalSales;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n;) {
            if (sales[i].venta_id == sales[j].venta_id) {
                printf("Duplicado encontrado: venta_id %d, eliminando registro duplicado.\n", sales[j].venta_id);
                // Eliminar el duplicado desplazando los elementos hacia la izquierda
                for (int k = j; k < n - 1; k++) {
                    sales[k] = sales[k + 1];
                }
                n--;
            } else {
                j++;
            }
        }
    }
    *totalSales = n;
}

// Funcion para calcular la moda de un array de valores enteros
int calcularModa(int *valores, int cantidad) {
    int maxCount = 0;
    int moda = valores[0];

    for (int i = 0; i < cantidad; i++) {
        int count = 0;
        for (int j = 0; j < cantidad; j++) {
            if (valores[j] == valores[i]) {
                count++;
            }
        }

        if (count > maxCount) {
            maxCount = count;
            moda = valores[i];
        }
    }

    return moda;
}


// Funcion para calcular la media de un array de valores
double calcularMedia(double *valores, int cantidad) {
    double suma = 0.0;
    for (int i = 0; i < cantidad; i++) {
        suma += valores[i];
    }
    return suma / cantidad;
}


void completarDatos(Sale *sales, int totalSales) {
    int *cantidades = (int *)malloc(totalSales * sizeof(int));
    double *precios = (double *)malloc(totalSales * sizeof(double));

    int totalCantidades = 0;
    int totalPrecios = 0;

    // Recopilar datos de cantidad y precio_unitario que no sean 0
    for (int i = 0; i < totalSales; i++) {
        if (sales[i].cantidad > 0) {
            cantidades[totalCantidades++] = sales[i].cantidad;
        }
        if (sales[i].precio_unitario > 0.0) {
            precios[totalPrecios++] = sales[i].precio_unitario;
        }
    }

    // Calcular moda para cantidad
    int modaCantidad = totalCantidades > 0 ? calcularModa(cantidades, totalCantidades) : 0;

    // Calcular media para precio_unitario
    double mediaPrecio = totalPrecios > 0 ? calcularMedia(precios, totalPrecios) : 0;

    // Completar datos faltantes
    for (int i = 0; i < totalSales; i++) {
        if (sales[i].cantidad == 0) {
            sales[i].cantidad = modaCantidad;
            printf("Cantidad completada en venta_id %d con valor %d (moda)\n", sales[i].venta_id, sales[i].cantidad);
        }
        if (sales[i].precio_unitario == 0.0) {
            sales[i].precio_unitario = mediaPrecio;
            printf("Precio unitario completado en venta_id %d con valor %.2f (media)\n", sales[i].venta_id, sales[i].precio_unitario);
        }
        // Actualizar el total de la linea
        sales[i].total = sales[i].cantidad * sales[i].precio_unitario;
    }

    free(cantidades);
    free(precios);
}

void procesarDatos(Sale *sales, int *totalSales) {

    if (sales == NULL || *totalSales == 0) {
        printf("No hay datos cargados para procesar.\n");
        return;
    }

    // Eliminar duplicados
    eliminarDuplicados(sales, totalSales);
    printf("Datos duplicados eliminados. Total de ventas despues de la limpieza: %d\n", totalSales);

    // Completar datos faltantes
    completarDatos(sales, *totalSales);
    printf("Datos faltantes completados.\n");
}