#include <stdio.h> 
#include "../lib/cJSON/cJSON.h" 
#include "./utils.h"

void showMenu() 
{
    printf("\n--- Sistema de Analisis de Datos de Ventas ---\n");
    printf("1. Importacion de datos\n");
    printf("2. Procesamiento de datos\n");
    printf("3. Analisis de datos\n");
    printf("4. Analisis temporal\n");
    printf("5. Estadisticas\n");
    printf("6. Salir\n");
    printf("Seleccione una opcion: ");    
}
  
int main() 
{ 
    int option;
    char filename[256];  
    Sale *sales = NULL;  
    int totalSales = 0;  

    do {
        showMenu();
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("Importacion de datos\n");
                printf("Ingrese la ruta del archivo JSON: ");
                scanf("%s", filename);
                dataImport(filename, &sales, &totalSales);
                printf("Datos importados correctamente. Total de ventas: %d\n", totalSales);
                break;
            case 2:
                printf("Procesamiento de datos\n");
                dataProcessing(sales, &totalSales);
                break;
            case 3:
                printf("Analisis de datos\n");
                printf("Total de ventas: %.2f\n", totalVentas(sales, totalSales));
                ventasMensualesYAnuales(sales, totalSales);
                break;
            case 4:
                printf("Analisis temporal\n");
                analisisTemporal(sales, totalSales);
                double tasa = calcularTasaCrecimiento(sales, totalSales, 2023, 1);
                printf("Tasa de crecimiento en el primer trimestre de 2023: %.2f%%\n", tasa);
                break;
            case 5:
                printf("Estadisticas\n");
                mostrarTop5Categorias(sales, totalSales);
                break;
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    } while (option != 6);
    return 0;
}
