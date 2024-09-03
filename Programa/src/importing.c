#include "headers.h"

void mostrarDatosImportados(Sale *sales, int totalSales) {
    printf("+-----------+------------+-------------+----------------+---------------+----------+----------------+---------+\n");
    printf("| Venta ID  |   Fecha    | Producto ID | Nombre Producto|   Categoria   | Cantidad | Precio Unitario|  Total  |\n");
    printf("+-----------+------------+-------------+----------------+---------------+----------+----------------+---------+\n");

    for (int i = 0; i < totalSales; i++) {
        printf("| %9d | %10s | %11d | %14s | %13s | %8d | %14.2f | %7.2f |\n",
               sales[i].venta_id,
               sales[i].fecha,
               sales[i].producto_id,
               sales[i].producto_nombre,
               sales[i].categoria,
               sales[i].cantidad,
               sales[i].precio_unitario,
               sales[i].total);
    }

    printf("+-----------+------------+-------------+----------------+---------------+----------+----------------+---------+\n");
}

char* leerArchivo(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char *)malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);
    data[length] = '\0';
    return data;
}

void parseJSON(const char *data, Sale **sales, int *totalSales) {
    // Parsear el archivo JSON
    cJSON *json = cJSON_Parse(data);
    if (!json) {
        printf("Error al parsear el archivo JSON.\n");
        return;
    }

    int count = cJSON_GetArraySize(json);
    *sales = (Sale *)realloc(*sales, (*totalSales + count) * sizeof(Sale));

    for (int i = 0; i < count; i++) {
        cJSON *item = cJSON_GetArrayItem(json, i);
        if (!item) continue; 

        // Extraer los campos del objeto JSON
        cJSON *venta_id = cJSON_GetObjectItem(item, "venta_id");
        cJSON *fecha = cJSON_GetObjectItem(item, "fecha");
        cJSON *producto_id = cJSON_GetObjectItem(item, "producto_id");
        cJSON *producto_nombre = cJSON_GetObjectItem(item, "producto_nombre");
        cJSON *categoria = cJSON_GetObjectItem(item, "categoria");
        cJSON *cantidad = cJSON_GetObjectItem(item, "cantidad");
        cJSON *precio_unitario = cJSON_GetObjectItem(item, "precio_unitario");
        cJSON *total = cJSON_GetObjectItem(item, "total");

        if (!venta_id || !fecha || !producto_id || !producto_nombre || !categoria) {
            printf("Faltan datos en la línea %d. No se ha incluido.\n", i + 1);
            continue;
        }

        // Asignar los valores a la estructura Sale
        (*sales)[*totalSales].venta_id = (short int)venta_id->valueint;
        strcpy((*sales)[*totalSales].fecha, fecha->valuestring);
        (*sales)[*totalSales].producto_id = (short int)producto_id->valueint;

        (*sales)[*totalSales].producto_nombre = strdup(producto_nombre->valuestring);
        (*sales)[*totalSales].categoria = strdup(categoria->valuestring);

        (*sales)[*totalSales].cantidad = cantidad ? cantidad->valueint : 0;
        (*sales)[*totalSales].precio_unitario = precio_unitario ? precio_unitario->valuedouble : 0.0;
        (*sales)[*totalSales].total = total ? total->valuedouble : 0.0;

        (*totalSales)++;
    }

    cJSON_Delete(json);
}

void importacionDatos(const char *filename, Sale **sales, int *totalSales) {
    char *data = leerArchivo(filename);
    if (!data) return;

    parseJSON(data, sales, totalSales);
    free(data);

    mostrarDatosImportados(*sales, *totalSales);
}