#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SERVER_FIFO "server_fifo"
#define BUFFER_SIZE 256

int main() {
    char fd[BUFFER_SIZE];
    snprintf(fd, BUFFER_SIZE, "/tmp/client_fifo_%d", getpid());

    if (mkfifo(fd, 0666) < 0) {
        perror("Error: cannot create client FIFO");
        exit(EXIT_FAILURE);
    }

    int fd2 = open(SERVER_FIFO, O_WRONLY);
    if (fd2 < 0) {
        perror("Error: cannot open server FIFO");
        unlink(fd);
        exit(EXIT_FAILURE);
    }

    write(fd2, fd, strlen(fd) + 1);
    close(fd2);

    int fd3 = open(fd, O_RDWR);
    if (fd3 < 0) {
        perror("Error: cannot open client FIFO");
        unlink(fd);
        exit(EXIT_FAILURE);
    }

    char command[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    while (1) {
        printf("Write a command (or 'adios' to exit): ");
        fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strcmp(command, "adios") == 0) {
            break;
        }

        write(fd3, command, strlen(command) + 1);

        printf("Results of the command:\n");
        while (read(fd3, response, BUFFER_SIZE) > 0) {
            if (strncmp(response, "The end of the command", 22) == 0) {
                break;
            }
            printf("%s", response);
        }
    }

    close(fd3);
    unlink(fd);
    unlink(SERVER_FIFO);
    return 0;
}