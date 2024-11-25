#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int fd[2];
    pid_t pid;

    if(pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ls", "ls", NULL);
        exit(1);
    } else {
        close(fd[1]);
        dup2(fd[0], STDOUT_FILENO);
        close(fd[0]);
        execlp("wc", "wc", NULL);
        exit(1);
    }

    return 0;

}