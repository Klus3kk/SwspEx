#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    int fd[2];
    pid_t pid1, pid2, pid3;

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Proces 1: Generowanie liczb parzystych
    pid1 = fork();
    if (pid1 == 0) {
        close(fd[0]); // Zamknięcie odczytu
        for (int i = 2; i <= 10; i += 2) { // Generowanie liczb parzystych od 2 do 10
            write(fd[1], &i, sizeof(int));
        }
        close(fd[1]); // Zamknięcie zapisu
        exit(0);
    }

    // Proces 2: Generowanie liczb nieparzystych
    pid2 = fork();
    if (pid2 == 0) {
        close(fd[0]); // Zamknięcie odczytu
        for (int i = 1; i <= 9; i += 2) { // Generowanie liczb nieparzystych od 1 do 9
            write(fd[1], &i, sizeof(int));
        }
        close(fd[1]); // Zamknięcie zapisu
        exit(0);
    }

    // Proces 3: Sumowanie liczb
    pid3 = fork();
    if (pid3 == 0) {
        close(fd[1]); // Zamknięcie zapisu
        int sum = 0, num;
        while (read(fd[0], &num, sizeof(int)) > 0) {
            sum += num;
        }
        close(fd[0]); // Zamknięcie odczytu
        printf("Suma liczb: %d\n", sum);
        exit(0);
    }

    // Zamknięcie potoku w procesie macierzystym
    close(fd[0]);
    close(fd[1]);

    // Oczekiwanie na zakończenie procesów potomnych
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
