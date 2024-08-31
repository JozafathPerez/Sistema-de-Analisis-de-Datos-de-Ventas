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

typedef struct {
    int mes;
    double totalVentas;
} VentasMensuales;

typedef struct {
    int ano;
    VentasMensuales *ventasMensuales; // Array dinámico de ventas mensuales
    int totalMeses;
} VentasAnuales;


void mostrarDatosImportados(Sale *sales, int totalSales);

/*****Nombre***************************************
 * importacionDatos
 *****Descripción**********************************
* Importa los datos de ventas desde un archivo JSON y los almacena 
* en un arreglo de estructuras `Sale`. 
*
 *****Retorno**************************************
* Esta función no retorna ningún valor. Los datos importados se 
* almacenan en el puntero `sales` y el número total de ventas 
* en `totalSales`.
*
 *****Entradas*************************************
* - filename: Nombre del archivo JSON que contiene los datos de ventas.
* - sales: Puntero a un arreglo de estructuras `Sale` donde se 
*   almacenarán los datos importados.
* - totalSales: Puntero a un entero donde se almacenará el número 
*   total de ventas importadas.
**************************************************/
void importacionDatos(const char *filename, Sale **sales, int *totalSales);

/*****Nombre***************************************
 * eliminarDuplicados
 *****Descripción**********************************
* Elimina las ventas duplicadas en el arreglo de estructuras `Sale`, 
* asegurando que cada venta sea única en función de un criterio específico 
* (como ID de venta). Actualiza el número total de ventas.
*
 *****Retorno**************************************
* Esta función no retorna ningún valor. Modifica el arreglo `sales` y 
* actualiza `totalSales` para reflejar la eliminación de duplicados.
*
 *****Entradas*************************************
* - sales: Arreglo de estructuras `Sale` que contiene los datos de ventas.
* - totalSales: Puntero al número total de ventas, que será actualizado 
*   después de eliminar los duplicados.
**************************************************/
void eliminarDuplicados(Sale *sales, int *totalSales);

/*****Nombre***************************************
 * calcularModa
 *****Descripción**********************************
* Calcula la moda (el valor que aparece con mayor frecuencia) de un 
* conjunto de datos enteros.
*
 *****Retorno**************************************
* Retorna la moda como un valor de tipo `int`. Si hay múltiples modas, 
* retorna una de ellas.
*
 *****Entradas*************************************
* - valores: Arreglo de enteros que contiene los valores para los 
*   cuales se calculará la moda.
* - cantidad: Número total de valores en el arreglo `valores`.
**************************************************/
int calcularModa(int *valores, int cantidad);

/*****Nombre***************************************
 * calcularMedia
 *****Descripción**********************************
* Calcula la media (promedio) de un conjunto de datos de tipo `double`.
*
 *****Retorno**************************************
* Retorna la media como un valor de tipo `double`.
*
 *****Entradas*************************************
* - valores: Arreglo de valores de tipo `double` para los cuales 
*   se calculará la media.
* - cantidad: Número total de valores en el arreglo `valores`.
**************************************************/
double calcularMedia(double *valores, int cantidad);

/*****Nombre***************************************
 * completarDatos
 *****Descripción**********************************
* Completa los datos faltantes en el arreglo de ventas `sales` 
* utilizando técnicas como la moda o la media para estimar valores 
* faltantes en los campos `cantidad` y `precio_unitario`.
*
 *****Retorno**************************************
* Esta función no retorna ningún valor. Modifica los datos de ventas 
* en el arreglo `sales`.
*
 *****Entradas*************************************
* - sales: Arreglo de estructuras `Sale` que contiene los datos de ventas.
* - totalSales: Número total de ventas.
**************************************************/
void completarDatos(Sale *sales, int totalSales);

/*****Nombre***************************************
 * procesarDatos
 *****Descripción**********************************
* Realiza el procesamiento de los datos de ventas, como la eliminación 
* de duplicados y la corrección de datos faltantes. 
*
 *****Retorno**************************************
* Esta función no retorna ningún valor. Procesa y modifica los 
* datos almacenados en `sales` y actualiza `totalSales` si es necesario.
*
 *****Entradas*************************************
* - sales: Arreglo de estructuras `Sale` que contiene los datos de ventas 
*   a ser procesados.
* - totalSales: Puntero al número total de ventas, que puede ser 
*   modificado si se eliminan duplicados.
**************************************************/
void procesarDatos(Sale *sales, int *totalSales);

/*****Nombre***************************************
 * totalVentas
 *****Descripción**********************************
* Calcula el total de ventas sumando los importes de todas las 
* transacciones registradas.
*
 *****Retorno**************************************
* Retorna el total de ventas como un valor de tipo `double`.
*
 *****Entradas*************************************
* - sales: Arreglo de estructuras `Sale` que contiene los datos de ventas.
* - totalSales: Número total de ventas.
**************************************************/
double totalVentas(Sale *sales, int totalSales);

void agregarVenta(VentasAnuales **ventasAnuales, int *totalAnos, int ano, int mes, double total);

const char* obtenerNombreMes(int mes);

/*****Nombre***************************************
 * ventasMensualesYAnuales
 *****Descripción**********************************
* Calcula y muestra el total de ventas agrupado por mes y por año.
*
 *****Retorno**************************************
* Esta función no retorna ningún valor. Imprime los totales 
* mensuales y anuales en la salida estándar.
*
 *****Entradas*************************************
* - sales: Arreglo de estructuras `Sale` que contiene los datos de ventas.
* - totalSales: Número total de ventas.
**************************************************/
void ventasMensualesYAnuales(Sale *sales, int totalSales);

/*****Nombre***************************************
 * parseFecha
 *****Descripción**********************************
* Convierte una fecha en formato "yyyy-mm-dd" en una estructura `tm` 
* de C que contiene los componentes de la fecha (año, mes, día, etc.).
*
 *****Retorno**************************************
* Esta función no retorna ningún valor. Llena la estructura `tm` 
* con los valores correspondientes.
*
 *****Entradas*************************************
* - fecha: Cadena de caracteres que contiene la fecha en formato "yyyy-mm-dd".
* - tm: Puntero a una estructura `tm` que será llenada con los componentes 
*   de la fecha.
**************************************************/
// void parseFecha(const char *fecha, struct tm *tm);

/*****Nombre***************************************
 * analisisTemporal
 *****Descripción**********************************
* Realiza un análisis temporal sobre los datos de ventas, 
* identificando el mes con mayor venta y el día de la semana 
* más activo en términos de transacciones.
*
 *****Retorno**************************************
* Esta función no retorna ningún valor. Los resultados del 
* análisis se imprimen en la salida estándar.
*
 *****Entradas*************************************
* - sales: Arreglo de estructuras `Sale` que contiene los datos de ventas.
* - totalSales: Número total de ventas.
**************************************************/
void analisisTemporal(Sale *sales, int totalSales);

/*****Nombre***************************************
 * calcularTasaCrecimiento
 *****Descripción**********************************
* Calcula la tasa de crecimiento o decrecimiento de las ventas 
* en un trimestre específico.
*
 *****Retorno**************************************
* Retorna la tasa de crecimiento como un valor de tipo `double`.
*
 *****Entradas*************************************
* - sales: Arreglo de estructuras `Sale` que contiene los datos de ventas.
* - totalSales: Número total de ventas.
* - año: Año para el cual se calculará la tasa.
* - trimestre: Trimestre específico (1, 2, 3 o 4) para el cual 
*   se calculará la tasa.
**************************************************/
double calcularTasaCrecimiento(Sale *sales, int totalSales, int año, int trimestre);

/*****Nombre***************************************
 * mostrarTop5Categorias
 *****Descripción**********************************
* Identifica y muestra las 5 categorías con mayores ventas en 
* términos de monto total.
*
 *****Retorno**************************************
* Esta función no retorna ningún valor. Los resultados se 
* imprimen en la salida estándar.
*
 *****Entradas*************************************
* - sales: Arreglo de estructuras `Sale` que contiene los datos de ventas.
* - totalSales: Número total de ventas.
**************************************************/
void mostrarTop5Categorias(Sale *sales, int totalSales);

/*****Nombre***************************************
 * freeSales
 *****Descripción**********************************
* Libera la memoria asignada para las estructuras `Sale` 
* y sus componentes dinámicos.
*
 *****Retorno**************************************
* Esta función no retorna ningún valor. Libera los recursos 
* asociados a las ventas.
*
 *****Entradas*************************************
* - sales: Arreglo de estructuras `Sale` cuyas componentes 
*   deben ser liberadas.
* - totalSales: Número total de ventas a liberar.
**************************************************/
void freeSales(Sale *sales, int totalSales);

#endif
