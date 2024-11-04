#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    int fd[2];
    pid_t pid;
    char buffer[1024];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        close(fd[0]);  
        write(fd[1], "Hallo", 5);
        printf("Wypisano\n");
        close(fd[1]);  
        return 0;
    } else {
        if (pid == -1) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            close(fd[1]);  
            read(fd[0], buffer, sizeof(buffer));
            printf("Odczytano\n");
            close(fd[0]);  
            return 0;
        }
    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}
