#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    clock_t start, end;

    start = clock();

    // Primer fork
    pid1 = fork();
    if (pid1 == 0) {
        // Código del proceso hijo

        // Segundo fork
        pid2 = fork();
        if (pid2 == 0) {
            // Código del proceso nieto

            // Tercer fork
            pid3 = fork();
            if (pid3 == 0) {
                // Código del proceso bisnieto
                for (int i = 0; i < 1000000; i++) {
                    // Ciclo vacío
                    printf("%d\n", i);
                }
            } else {
                // Espera a que el proceso bisnieto termine
                wait(NULL);
                for (int i = 0; i < 1000000; i++) {
                    // Ciclo vacío
                    printf("%d\n", i);
                }
            }
        } else {
            // Espera a que el proceso nieto termine
            wait(NULL);
            for (int i = 0; i < 1000000; i++) {
                // Ciclo vacío
                printf("%d\n", i);
            }
        }
    } else {
        // Espera a que el proceso hijo termine
        wait(NULL);
        end = clock();
        // Calcula la diferencia de tiempo
        double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tiempo del CPU usado: %f segundos\n", cpu_time_used);
    }

    return 0;
}
