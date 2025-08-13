#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

// Función recursiva para factorial
unsigned long long facto_r(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * facto_r(n - 1);
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

    // Calcular factorial
    resultado = facto_r(num);

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
