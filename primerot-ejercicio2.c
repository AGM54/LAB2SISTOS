#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;
    
    
    start = clock();
    
    // Primer ciclo for de un millón de iteraciones
    for (int i = 0; i < 1000000; i++) {
        //
        printf("%d\n", i);
    }
    
    // Segundo ciclo for de un millón de iteraciones
    for (int i = 0; i < 1000000; i++) {
        // No hacer nada
        printf("%d\n", i);
    }
    
    // Tercer ciclo for de un millón de iteraciones
    for (int i = 0; i < 1000000; i++) {
        // No hacer nada
        printf("%d\n", i);
    }
    
    // Almacenar el tiempo actual en la variable 'end'
    end = clock();
    
    // Calcular la diferencia de tiempo y convertirlo a segundos
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    

    printf("Tiempo del CPU usado: %f segundos\n", cpu_time_used);
    
    return 0;
}
