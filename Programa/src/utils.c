#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

void dataImport(const char *filename, Sale **sales, int *totalSales) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo: %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char *)malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);
    data[length] = '\0';

    cJSON *json = cJSON_Parse(data);
    if (!json) {
        printf("Error al parsear el archivo JSON.\n");
        free(data);
        return;
    }

    int count = cJSON_GetArraySize(json);
    *sales = (Sale *)realloc(*sales, (*totalSales + count) * sizeof(Sale));

    for (int i = 0; i < count; i++) {
        cJSON *item = cJSON_GetArrayItem(json, i);

        cJSON *venta_id = cJSON_GetObjectItem(item, "venta_id");
        cJSON *fecha = cJSON_GetObjectItem(item, "fecha");
        cJSON *producto_id = cJSON_GetObjectItem(item, "producto_id");
        cJSON *producto_nombre = cJSON_GetObjectItem(item, "producto_nombre");
        cJSON *categoria = cJSON_GetObjectItem(item, "categoria");
        cJSON *cantidad = cJSON_GetObjectItem(item, "cantidad");
        cJSON *precio_unitario = cJSON_GetObjectItem(item, "precio_unitario");
        cJSON *total = cJSON_GetObjectItem(item, "total");

        if (!venta_id || !fecha || !producto_id || !producto_nombre || !categoria) {
            printf("Faltan datos en la linea %d. No se ha incluido.\n", i + 1);
            continue;
        }

        // Usar short int para ids y longitud fija para fecha
        (*sales)[*totalSales].venta_id = (short int)venta_id->valueint;
        strcpy((*sales)[*totalSales].fecha, fecha->valuestring);
        (*sales)[*totalSales].producto_id = (short int)producto_id->valueint;

        // Asignacion dinamica para producto_nombre y categoria
        (*sales)[*totalSales].producto_nombre = (char *)malloc(strlen(producto_nombre->valuestring) + 1);
        strcpy((*sales)[*totalSales].producto_nombre, producto_nombre->valuestring);

        (*sales)[*totalSales].categoria = (char *)malloc(strlen(categoria->valuestring) + 1);
        strcpy((*sales)[*totalSales].categoria, categoria->valuestring);

        (*sales)[*totalSales].cantidad = cantidad ? cantidad->valueint : 0;
        (*sales)[*totalSales].precio_unitario = precio_unitario ? precio_unitario->valuedouble : 0.0;
        (*sales)[*totalSales].total = total ? total->valuedouble : 0.0;

        (*totalSales)++;
    }

    cJSON_Delete(json);
    free(data);
}

// Funcion para calcular la media de un array de valores
double calcularMedia(double *valores, int cantidad) {
    double suma = 0.0;
    for (int i = 0; i < cantidad; i++) {
        suma += valores[i];
    }
    return suma / cantidad;
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

void RemoveDuplicates(Sale *sales, int *totalSales) {
    for (int i = 0; i < *totalSales; i++) {
        for (int j = i + 1; j < *totalSales; j++) {
            if (sales[i].venta_id == sales[j].venta_id) {
                // Liberar memoria de la venta duplicada
                free(sales[j].producto_nombre);
                free(sales[j].categoria);

                // Mover los elementos restantes hacia la izquierda
                for (int k = j; k < *totalSales - 1; k++) {
                    sales[k] = sales[k + 1];
                }

                (*totalSales)--;
                j--;  // Para revisar el nuevo elemento en la posicion j
            }
        }
    }
}

void completeData(Sale *sales, int totalSales) {
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

void dataProcessing(Sale *sales, int *totalSales) {

    if (sales == NULL || *totalSales == 0) {
        printf("No hay datos cargados para procesar.\n");
        return;
    }

    // Eliminar duplicados
    RemoveDuplicates(sales, totalSales);
    printf("Datos duplicados eliminados. Total de ventas despues de la limpieza: %d\n", totalSales);

    // Completar datos faltantes
    completeData(sales, *totalSales);
    printf("Datos faltantes completados.\n");
}

double totalVentas(Sale *sales, int totalSales) {
    double total = 0.0;
    for (int i = 0; i < totalSales; i++) {
        total += sales[i].total;
    }
    return total;
}

void ventasMensualesYAnuales(Sale *sales, int totalSales) {
    double ventasMensuales[12] = {0};
    double ventasAnuales[100] = {0}; // Asume que manejas hasta 100 anos distintos como maximo
    int anos[100] = {0}; // Almacenar los anos distintos encontrados
    int totalAnos = 0;

    for (int i = 0; i < totalSales; i++) {
        int mes = atoi(&sales[i].fecha[5]) - 1; // Extraer el mes
        int ano = atoi(&sales[i].fecha[0]); // Extraer el ano

        ventasMensuales[mes] += sales[i].total;

        // Buscar si el ano ya esta registrado
        int anoIndex = -1;
        for (int j = 0; j < totalAnos; j++) {
            if (anos[j] == ano) {
                anoIndex = j;
                break;
            }
        }

        // Si no lo esta, agregarlo
        if (anoIndex == -1) {
            anos[totalAnos] = ano;
            ventasAnuales[totalAnos] = sales[i].total;
            totalAnos++;
        } else {
            ventasAnuales[anoIndex] += sales[i].total;
        }
    }

    printf("\nVentas Mensuales:\n");
    for (int i = 0; i < 12; i++) {
        printf("Mes %d: %.2f\n", i + 1, ventasMensuales[i]);
    }

    printf("\nVentas Anuales:\n");
    for (int i = 0; i < totalAnos; i++) {
        printf("Ano %d: %.2f\n", anos[i], ventasAnuales[i]);
    }
}


void parseFecha(const char *fecha, struct tm *tm) {
    sscanf(fecha, "%Y-%m-%d", &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
    tm->tm_year -= 1900; // Ajustar ano
    tm->tm_mon -= 1; // Ajustar mes
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    tm->tm_isdst = -1; // No aplicar horario de verano
}

void analisisTemporal(Sale *sales, int totalSales) {
    double ventasMensuales[12] = {0};
    int transaccionesDia[7] = {0}; // 0: Domingo, 1: Lunes, ..., 6: Sabado

    for (int i = 0; i < totalSales; i++) {
        // Calcular el mes
        int mes = atoi(&sales[i].fecha[5]) - 1; 
        ventasMensuales[mes] += sales[i].total;

        // Calcular el dia de la semana
        struct tm tm = {0};
        parseFecha(sales[i].fecha, &tm);
        mktime(&tm);
        int diaSemana = tm.tm_wday;

        transaccionesDia[diaSemana]++;
    }

    // Encontrar el mes con mayor venta
    int mesMayorVenta = 0;
    for (int i = 1; i < 12; i++) {
        if (ventasMensuales[i] > ventasMensuales[mesMayorVenta]) {
            mesMayorVenta = i;
        }
    }

    // Encontrar el dia con mas transacciones
    int diaMasActivo = 0;
    for (int i = 1; i < 7; i++) {
        if (transaccionesDia[i] > transaccionesDia[diaMasActivo]) {
            diaMasActivo = i;
        }
    }

    printf("\nMes con mayor venta: %d con un total de %.2f\n", mesMayorVenta + 1, ventasMensuales[mesMayorVenta]);
    printf("Dia de la semana mas activo: %d (0: Domingo, 6: Sabado) con %d transacciones\n", diaMasActivo, transaccionesDia[diaMasActivo]);
}


double calcularTasaCrecimiento(Sale *sales, int totalSales, int ano, int trimestre) {
    double ventasTrimestre[4] = {0}; // Ventas por cada trimestre

    for (int i = 0; i < totalSales; i++) {
        int anoVenta = atoi(&sales[i].fecha[0]);
        int mesVenta = atoi(&sales[i].fecha[5]);

        if (anoVenta == ano) {
            int indexTrimestre = (mesVenta - 1) / 3;
            ventasTrimestre[indexTrimestre] += sales[i].total;
        }
    }

    double tasa = 0.0;
    if (trimestre > 1) {
        double ventasPrevias = ventasTrimestre[trimestre - 2];
        double ventasActuales = ventasTrimestre[trimestre - 1];
        if (ventasPrevias != 0) {
            tasa = ((ventasActuales - ventasPrevias) / ventasPrevias) * 100;
        }
    }
    return tasa;
}


void mostrarTop5Categorias(Sale *sales, int totalSales) {
    typedef struct {
        char *categoria;
        double totalVentas;
    } CategoriaTotal;

    CategoriaTotal categorias[100] = {0}; 
    int totalCategorias = 0;

    for (int i = 0; i < totalSales; i++) {
        int indexCategoria = -1;
        for (int j = 0; j < totalCategorias; j++) {
            if (strcmp(categorias[j].categoria, sales[i].categoria) == 0) {
                indexCategoria = j;
                break;
            }
        }

        if (indexCategoria == -1) {
            categorias[totalCategorias].categoria = sales[i].categoria;
            categorias[totalCategorias].totalVentas = sales[i].total;
            totalCategorias++;
        } else {
            categorias[indexCategoria].totalVentas += sales[i].total;
        }
    }

    // Ordenar categorias por ventas totales
    for (int i = 0; i < totalCategorias - 1; i++) {
        for (int j = i + 1; j < totalCategorias; j++) {
            if (categorias[j].totalVentas > categorias[i].totalVentas) {
                CategoriaTotal temp = categorias[i];
                categorias[i] = categorias[j];
                categorias[j] = temp;
            }
        }
    }

    printf("\nTop 5 Categorias con mayores ventas:\n");
    for (int i = 0; i < 5 && i < totalCategorias; i++) {
        printf("%d. %s: %.2f\n", i + 1, categorias[i].categoria, categorias[i].totalVentas);
    }
}

void freeSales(Sale *sales, int totalSales) {
    for (int i = 0; i < totalSales; i++) {
        free(sales[i].producto_nombre);
        free(sales[i].categoria);
    }
    free(sales);
}
