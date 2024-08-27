/*****Datos administrativos************************
* Nombre del archivo: Utils.h
* Tipo de archivo: Encabezado (.h)
* Proyecto: Sistema de Analisis de Datos de Ventas
* Autores: Jozafath Perez
* Empresa: Social mold
*****Descripción**********************************
* 
*****Versión**************************************
* ##    | Fecha y hora | Autore
* 0.0.1 | 17/08/2024   | Jozafath Perez
**************************************************/


#ifndef UTILS_H
#define UTILS_H

#include "../lib/cJSON/cJSON.h"

typedef struct {
    short int venta_id;
    char fecha[11];  // Fecha en formato "yyyy-mm-dd"
    short int producto_id;
    char *producto_nombre;  
    char *categoria;        
    int cantidad;
    double precio_unitario;
    double total;
} Sale;



/*****Nombre***************************************
 * 
 *****Descripción**********************************
* 
*****Retorno**************************************
* 
*****Entradas*************************************
* 
**************************************************/
void dataImport(const char *filename, Sale **sales, int *totalSales);


/*****Nombre***************************************
 * 
 *****Descripción**********************************
* 
*****Retorno**************************************
* 
*****Entradas*************************************
* 
**************************************************/
void dataProcessing(Sale *sales, int *totalSales);


double totalVentas(Sale *sales, int totalSales);


void ventasMensualesYAnuales(Sale *sales, int totalSales);

void analisisTemporal(Sale *sales, int totalSales);

double calcularTasaCrecimiento(Sale *sales, int totalSales, int año, int trimestre);

void mostrarTop5Categorias(Sale *sales, int totalSales);


/*****Nombre***************************************
 * 
 *****Descripción**********************************
* 
*****Retorno**************************************
* 
*****Entradas*************************************
* 
**************************************************/
void freeSales(Sale *sales, int totalSales);
#endif