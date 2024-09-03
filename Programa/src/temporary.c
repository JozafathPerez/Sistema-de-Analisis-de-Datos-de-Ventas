#include "headers.h"

void parseFecha(const char *fecha, struct tm *tm) {
    // Extrae año, mes y día de una cadena en formato "yyyy-mm-dd" y los asigna a la estructura tm.
    sscanf(fecha, "%4d-%2d-%2d", &tm->tm_year, &tm->tm_mon, &tm->tm_mday);
    tm->tm_year -= 1900; // Ajusta el año
    tm->tm_mon -= 1; // Ajusta el mes
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    tm->tm_isdst = -1; // No aplicar horario de verano
}

void calcularVentasMensuales(Sale *sales, int totalSales, double *ventasMensuales) {
    
    for (int i = 0; i < totalSales; i++) {
        struct tm tm = {0};
        parseFecha(sales[i].fecha, &tm); // Convertir la fecha a una estructura tm
        int mes = tm.tm_mon; // 0: Enero, 1: Febrero, ..., 11: Diciembre
        ventasMensuales[mes] += sales[i].total;
    }
}

void calcularTransaccionesDiarias(Sale *sales, int totalSales, int *transaccionesDia) {
    for (int i = 0; i < totalSales; i++) {
        struct tm tm = {0};
        parseFecha(sales[i].fecha, &tm); // Convertir la fecha a una estructura tm
        mktime(&tm); // Normalizar la estructura tm
        int diaSemana = tm.tm_wday; // 0: Domingo, 1: Lunes, ..., 6: Sábado
        transaccionesDia[diaSemana]++;
    }
}

void analisisTemporal(Sale *sales, int totalSales) {
    double ventasMensuales[12] = {0};
    int transaccionesDia[7] = {0}; // 0: Domingo, 1: Lunes, ..., 6: Sábado

    // Calcular las ventas mensuales y transacciones diarias
    calcularVentasMensuales(sales, totalSales, ventasMensuales);
    calcularTransaccionesDiarias(sales, totalSales, transaccionesDia);

    // Encontrar el mes con mayor venta
    int mesMayorVenta = 0;
    for (int i = 1; i < 12; i++) {
        if (ventasMensuales[i] > ventasMensuales[mesMayorVenta]) {
            mesMayorVenta = i;
        }
    }

    // Encontrar el día de la semana con más transacciones
    int diaMasActivo = 0;
    for (int i = 1; i < 7; i++) {
        if (transaccionesDia[i] > transaccionesDia[diaMasActivo]) {
            diaMasActivo = i;
        }
    }

    // Imprimir resultados de ventas mensuales
    printf("\nMes con mayor venta:\n");
    printf("  %s: %.2f\n", obtenerNombreMes(mesMayorVenta + 1), ventasMensuales[mesMayorVenta]);

    // Imprimir resultados de transacciones diarias
    printf("\nDia de la semana mas activo:\n");
    printf("  %s: %d transacciones\n", obtenerNombreDia(diaMasActivo), transaccionesDia[diaMasActivo]);
}

double calcularTasaCrecimiento(Sale *sales, int totalSales, int ano, int trimestre) {
    double ventasTrimestre[4] = {0}; // Ventas por cada trimestre

    // Calcular ventas por trimestre
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
        double ventasPrevias = ventasTrimestre[trimestre - 2]; // Ventas del trimestre anterior
        double ventasActuales = ventasTrimestre[trimestre - 1]; // Ventas del trimestre actual
        if (ventasPrevias != 0) {
            tasa = ((ventasActuales - ventasPrevias) / ventasPrevias) * 100;
        }
    }
    return tasa;
}