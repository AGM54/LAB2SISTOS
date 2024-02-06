#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        // hijo
        printf("Proceos hijo.\n");
        _exit(0); 
    } else if (pid > 0) {
        //  padre
        printf("Proceso padre. Ahora se entra a un ciclo while infinito.\n");
        while(1) {
            // Ciclo infinito
        }
    } else {
        printf("Fallo al realizar fork().\n");
    }

    return 0; 
}
