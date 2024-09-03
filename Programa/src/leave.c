#include "headers.h"

void guardarDatos(const char *filename, Sale *sales, int totalSales) {
    // Crear un objeto JSON que contenga un arreglo de ventas
    cJSON *jsonArray = cJSON_CreateArray();

    for (int i = 0; i < totalSales; i++) {
        cJSON *jsonSale = cJSON_CreateObject();
        
        // Agregar los campos de la estructura Sale al objeto JSON
        cJSON_AddNumberToObject(jsonSale, "venta_id", sales[i].venta_id);
        cJSON_AddStringToObject(jsonSale, "fecha", sales[i].fecha);
        cJSON_AddNumberToObject(jsonSale, "producto_id", sales[i].producto_id);
        cJSON_AddStringToObject(jsonSale, "producto_nombre", sales[i].producto_nombre);
        cJSON_AddStringToObject(jsonSale, "categoria", sales[i].categoria);
        cJSON_AddNumberToObject(jsonSale, "cantidad", sales[i].cantidad);
        cJSON_AddNumberToObject(jsonSale, "precio_unitario", sales[i].precio_unitario);
        cJSON_AddNumberToObject(jsonSale, "total", sales[i].total);

        cJSON_AddItemToArray(jsonArray, jsonSale);
    }

    char *jsonString = cJSON_Print(jsonArray);
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", jsonString);
        fclose(file);
    } else {
        printf("No se pudo abrir el archivo para guardar.\n");
    }

    // Liberar memoria
    cJSON_Delete(jsonArray);
    free(jsonString);
}