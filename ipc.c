#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define NOMBRE_SHM "mi_memoria_compartida"
#define TAMANO_SHM 1024  // Tamaño total de la memoria compartida

int main(int argc, char *argv[]) {
    // Verifica los argumentos
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <caracter> <id_proceso>\n", argv[0]);
        exit(1);
    }

    char caracter = argv[1][0]; // El carácter a escribir en la memoria compartida
    int id = atoi(argv[2]);      // Identificador del proceso (a o b)

    // Imprime cuál instancia es
    printf("Soy %c\n", id == 1 ? 'a' : 'b');

    // Abre (o crea si es necesario) un objeto de memoria compartida
    int fd_shm = shm_open(NOMBRE_SHM, O_CREAT | O_RDWR, 0666);
    if (fd_shm < 0) {
        perror("shm_open");
        exit(1);
    }

    // Ajusta el tamaño de la memoria compartida
    if (ftruncate(fd_shm, TAMANO_SHM) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Mapea la memoria compartida
    void *ptr_shm = mmap(0, TAMANO_SHM, PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (ptr_shm == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("%c: Puntero creado con el valor %p\n", id == 1 ? 'a' : 'b', ptr_shm);

    // Escribe en la memoria compartida en diferentes desplazamientos basados en el ID
    int desplazamiento = (id == 1) ? 0 : TAMANO_SHM / 2; // La mitad de la memoria para cada proceso
    memset((char*)ptr_shm + desplazamiento, caracter, TAMANO_SHM / 2); // Escribe solo en la mitad asignada
    printf("%c: Objeto de memoria compartida inicializado en desplazamiento %d\n", id == 1 ? 'a' : 'b', desplazamiento);

    // Espera un poco para que el otro proceso tenga tiempo de escribir también
    sleep(1);

    // Imprime el contenido de la memoria compartida
    printf("%c: La memoria compartida tiene: %.*s\n", id == 1 ? 'a' : 'b', TAMANO_SHM, (char *)ptr_shm);

    // Limpieza
    munmap(ptr_shm, TAMANO_SHM);
    close(fd_shm);

    // Solo el último proceso que se ejecuta debería eliminar la memoria compartida
    if (id == 2) {
        shm_unlink(NOMBRE_SHM);
    }

    return 0;
}
