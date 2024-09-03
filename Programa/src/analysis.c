#include "headers.h"

double totalVentas(Sale *sales, int totalSales) {
    // Calcular el total de ventas sumando los importes de todas las transacciones
    double total = 0.0;
    for (int i = 0; i < totalSales; i++) {
        total += sales[i].total;
    }
    return total;
}

void agregarVenta(VentasAnuales **ventasAnuales, int *totalAnos, int ano, int mes, double total) {
    for (int i = 0; i < *totalAnos; i++) {
        if ((*ventasAnuales)[i].ano == ano) {
            // Año encontrado, agregar o actualizar el mes
            for (int j = 0; j < (*ventasAnuales)[i].totalMeses; j++) {
                if ((*ventasAnuales)[i].ventasMensuales[j].mes == mes) {
                    (*ventasAnuales)[i].ventasMensuales[j].totalVentas += total;
                    return;
                }
            }
            // Si el mes no se encontró, agregarlo
            (*ventasAnuales)[i].ventasMensuales = (VentasMensuales *)realloc((*ventasAnuales)[i].ventasMensuales, ((*ventasAnuales)[i].totalMeses + 1) * sizeof(VentasMensuales));
            (*ventasAnuales)[i].ventasMensuales[(*ventasAnuales)[i].totalMeses].mes = mes;
            (*ventasAnuales)[i].ventasMensuales[(*ventasAnuales)[i].totalMeses].totalVentas = total;
            (*ventasAnuales)[i].totalMeses++;
            return;
        }
    }

    // Si el año no se encontró, agregarlo
    *ventasAnuales = (VentasAnuales *)realloc(*ventasAnuales, (*totalAnos + 1) * sizeof(VentasAnuales));
    (*ventasAnuales)[*totalAnos].ano = ano;
    (*ventasAnuales)[*totalAnos].ventasMensuales = (VentasMensuales *)malloc(sizeof(VentasMensuales));
    (*ventasAnuales)[*totalAnos].ventasMensuales[0].mes = mes;
    (*ventasAnuales)[*totalAnos].ventasMensuales[0].totalVentas = total;
    (*ventasAnuales)[*totalAnos].totalMeses = 1;
    (*totalAnos)++;
}



void ventasMensualesYAnuales(Sale *sales, int totalSales) {
    VentasAnuales *ventasAnuales = NULL;
    int totalAnos = 0;

    for (int i = 0; i < totalSales; i++) {
        int mes = atoi(&sales[i].fecha[5]); // Extraer el mes (sin -1 para representar el mes real)
        int ano = atoi(&sales[i].fecha[0]); // Extraer el año
        double total = sales[i].total;

        agregarVenta(&ventasAnuales, &totalAnos, ano, mes, total);
    }

    // Impresión de los resultados
    printf("\nVentas Anuales y Mensuales:\n");
    for (int i = 0; i < totalAnos; i++) {
        double totalAnual = 0.0;
        printf("\nAno %d:\n", ventasAnuales[i].ano);
        for (int j = 0; j < ventasAnuales[i].totalMeses; j++) {
            const char* nombreMes = obtenerNombreMes(ventasAnuales[i].ventasMensuales[j].mes);
            double totalMensual = ventasAnuales[i].ventasMensuales[j].totalVentas;
            printf("  %s: %.2f\n", nombreMes, totalMensual);
            totalAnual += totalMensual;
        }
        printf("  Total del ano %d: %.2f\n", ventasAnuales[i].ano, totalAnual);
    }

    // Liberar memoria
    for (int i = 0; i < totalAnos; i++) {
        free(ventasAnuales[i].ventasMensuales);
    }
    free(ventasAnuales);
}
