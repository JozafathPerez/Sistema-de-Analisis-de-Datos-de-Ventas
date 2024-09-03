#include "headers.h"

const char* obtenerNombreMes(int mes) {
    static const char* nombresMeses[] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", 
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };
    if (mes < 1 || mes > 12) return "Mes inválido";
    return nombresMeses[mes - 1];
}

const char* obtenerNombreDia(int dia) {
    static const char* nombresDias[] = {
        "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"
    };
    if (dia < 0 || dia > 6) return "Día inválido";
    return nombresDias[dia];
}

void freeSales(Sale *sales, int totalSales) {
    // Libera la memoria asignada dinámicamente para los nombres de productos y categorías.
    for (int i = 0; i < totalSales; i++) {
        free(sales[i].producto_nombre);
        free(sales[i].categoria);
    }
    free(sales);
}
