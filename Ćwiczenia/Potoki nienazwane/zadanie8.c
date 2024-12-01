#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Proces dziecka 1 (ls)
        close(fd[0]);                // Zamykamy czytanie potoku
        dup2(fd[1], STDOUT_FILENO);  // Przekierowujemy stdout do potoku
        close(fd[1]);                // Zamykamy deskryptor zapisu

        execlp("ls", "ls", NULL);    // Uruchamiamy ls
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Proces dziecka 2 (tr)
        close(fd[1]);                // Zamykamy zapis do potoku
        dup2(fd[0], STDIN_FILENO);   // Przekierowujemy stdin do potoku
        close(fd[0]);                // Zamykamy deskryptor czytania

        execlp("tr", "tr", "a-z", "A-Z", NULL); // Uruchamiamy tr
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Proces rodzica
    close(fd[0]);  // Zamykamy obydwa końce potoku
    close(fd[1]);

    wait(NULL);  // Oczekujemy na zakończenie procesów dziecka
    wait(NULL);

    return 0;
}
