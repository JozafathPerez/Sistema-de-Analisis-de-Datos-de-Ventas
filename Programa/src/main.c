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
    do {
        showMenu();
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("Importacion de datos\n");
                dataImport();
                break;
            case 2:
                printf("Procesamiento de datos\n");
                dataProcessing();
                break;
            case 3:
                printf("Analisis de datos\n");
                dataAnalysis();
                break;
            case 4:
                printf("Analisis temporal\n");
                temporalAnalysis();
                break;
            case 5:
                printf("Estadisticas\n");
                statistics();
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
