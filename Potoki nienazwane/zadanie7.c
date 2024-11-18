#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(fd[0]);               
        dup2(fd[1], STDOUT_FILENO);  
        close(fd[1]);                

        execlp("ls", "ls", NULL);    
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Proces rodzica (konwersja małych liter na wielkie)
    close(fd[1]);  // Zamykamy zapis do potoku

    char buffer[1024];
    ssize_t bytesRead;

    // Czytamy dane z potoku
    while ((bytesRead = read(fd[0], buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            buffer[i] = toupper(buffer[i]);  // Zamiana liter na wielkie
        }
        write(STDOUT_FILENO, buffer, bytesRead);  // Wyświetlanie przetworzonych danych
    }

    if (bytesRead == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);  // Zamykamy czytanie potoku
    wait(NULL);    // Oczekujemy na zakończenie procesu dziecka

    return 0;
}
