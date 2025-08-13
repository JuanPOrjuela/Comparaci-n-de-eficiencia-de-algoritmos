#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

// Función iterativa para factorial
unsigned long long facto_i(int n) {
    unsigned long long resultado = 1;
    for (int i = 1; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

int main() {
    int num;
    struct timeval start, end;
    struct rusage usage;
    unsigned long long resultado;
    double tiempo_usado;
    long memoria_kb;

    printf("Introduce un número para calcular su factorial: ");
    scanf("%d", &num);

    // Medir tiempo antes
    gettimeofday(&start, NULL);

    // Calcular factorial iterativo
    resultado = facto_i(num);

    // Medir tiempo después
    gettimeofday(&end, NULL);

    // Calcular tiempo en segundos
    tiempo_usado = (end.tv_sec - start.tv_sec) +
                   (end.tv_usec - start.tv_usec) / 1000000.0;

    // Medir uso de memoria
    getrusage(RUSAGE_SELF, &usage);
    memoria_kb = usage.ru_maxrss; // en KB

    printf("\nFactorial de %d = %llu\n", num, resultado);
    printf("Tiempo de ejecución: %.6f segundos\n", tiempo_usado);
    printf("Memoria máxima usada: %ld KB\n", memoria_kb);

    return 0;
}
