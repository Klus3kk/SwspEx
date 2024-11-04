#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid1, pid2, pid3;
    char buffer[1024];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid1 = fork();
    if (pid1 == 0) {
        close(fd[0]);
        write(fd[1], "Hallo: Process 1\n", 18);
        close(fd[1]);
        return 0;
    }

    pid2 = fork();
    if (pid2 == 0) {
        close(fd[0]);
        write(fd[1], "Hallo: Process 2\n", 18);
        close(fd[1]);
        return 0;
    }

    pid3 = fork();
    if (pid3 == 0) {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Read: Process 3 %s", buffer);
        close(fd[0]);
        return 0;
    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}
