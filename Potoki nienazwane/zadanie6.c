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
        close(fd[0]);                
        dup2(fd[1], STDOUT_FILENO);  
        close(fd[1]);               

        execlp("ls", "ls", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Proces dziecka 2 (wc)
        close(fd[1]);                // Zamykamy nieużywane wejście potoku
        dup2(fd[0], STDIN_FILENO);   // Przekierowujemy stdin do wyjścia potoku
        close(fd[0]);                // Zamykamy deskryptor potoku

        // Uruchamiamy `wc`
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);  // Zamykamy obydwa końce potoku
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
