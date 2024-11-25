#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define FIFO_NAME "meine_fifo"

int main() {
    pid_t pid;
    int fd;
    char buf[100];
    char *message = "HALLO!";

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
    } 

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            perror("open write");
            exit(1);
        }
        write(fd, message, strlen(message));
        close(fd);
        exit(0);
    } else {
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            perror("open read");
            exit(1);
        }
        read(fd, buf, sizeof(buf));
        printf("%s\n", buf);
        close(fd);

        unlink(FIFO_NAME);
    }
}