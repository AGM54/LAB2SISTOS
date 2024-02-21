#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        // Ejecuta la instancia 'a' de ipc
        execl("./ipc", "ipc", "a", "1", NULL);
        perror("execl");
        exit(1);
    } else if (pid > 0) { 
        sleep(1);
        execl("./ipc", "ipc", "b", "2", NULL);
        perror("execl");
        exit(1);
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}
