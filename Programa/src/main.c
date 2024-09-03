#include <stdio.h> 
#include "../lib/cJSON/cJSON.h" 
#include "./headers.h"

void showMenu() 
{
    printf("\n---------------------------------\n");
    printf("| Sistema de Analisis de Ventas |\n");
    printf("---------------------------------\n");
    printf("| 1. Importacion de datos       |\n");
    printf("| 2. Procesamiento de datos     |\n");
    printf("| 3. Analisis de datos          |\n");
    printf("| 4. Analisis temporal          |\n");
    printf("| 5. Estadisticas               |\n");
    printf("| 6. Salir                      |\n");
    printf("---------------------------------\n");
    printf("Seleccione una opcion: ");    
}

void clearB() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
  
int main() 
{ 
    int option;
    char filename[256];  
    Sale *sales = NULL;  
    int totalSales = 0;  
    
    importacionDatos("./data/sales.json", &sales, &totalSales);

    do {
        showMenu();
        if (scanf("%d", &option) != 1) {
            printf("\nEntrada invalida. Por favor, ingrese una opcion valida del 1 a 6.\n");
            clearB();
            continue; 
            }

        clearB();

        switch (option) {
            case 1:
                printf("\n-------------------------------\n");
                printf("|      Importacion de datos    |\n");
                printf("-------------------------------\n");
                printf("Ingrese la ruta del archivo JSON: ");
                scanf("%s", filename);
                importacionDatos(filename, &sales, &totalSales);
                printf("Datos importados correctamente. Total de ventas: %d\n", totalSales);
                break;
            case 2:
                printf("\n-------------------------------\n");
                printf("|     Procesamiento de datos   |\n");
                printf("-------------------------------\n");
                procesarDatos(sales, &totalSales);
                break;
            case 3:
                printf("---------------------------------\n");
                printf("|     Analisis de datos         |\n");
                printf("---------------------------------\n");
                printf("\nTotal de ventas: %.2f\n", totalVentas(sales, totalSales));
                printf("---------------------------------\n");
                ventasMensualesYAnuales(sales, totalSales);
                break;
            case 4:
                printf("\n-------------------------------\n");
                printf("|      Analisis temporal       |\n");
                printf("-------------------------------\n");
                analisisTemporal(sales, totalSales);
                double tasa = calcularTasaCrecimiento(sales, totalSales, 2023, 1);
                printf("\nTasa de crecimiento en el primer trimestre de 2023: %.2f%%\n", tasa);
                break;
            case 5:
                printf("\n-------------------------------\n");
                printf("|         Estadisticas         |\n");
                printf("-------------------------------\n");
                mostrarTop5Categorias(sales, totalSales);
                break;
            case 6:
                printf("\n-------------------------------\n");
                printf("|           Saliendo           |\n");
                printf("-------------------------------\n");
                guardarDatos("./data/sales.json", sales, totalSales);
                break;
            case 7:
                printf("\n-------------------------------\n");
                printf("|        Opcion oculta         |\n");
                printf("-------------------------------\n");
                mostrarDatosImportados(sales, totalSales);
                break;
            default:
                printf("\n-------------------------------\n");
                printf("|        Opcion no valida      |\n");
                printf("-------------------------------\n");
                break;
        }
    } while (option != 6);

    return 0;
}
