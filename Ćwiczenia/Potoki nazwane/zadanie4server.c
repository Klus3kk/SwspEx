// server 
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
    unlink(SERVER_FIFO);
    if (mkfifo(SERVER_FIFO, 0666) < 0) {
        perror("Error: cannot create server FIFO");
        exit(EXIT_FAILURE);
    }
    printf("---SERVER ACTIVATED---\n");

    while (1) {
        int fd = open(SERVER_FIFO, O_RDONLY);
        if (fd < 0) {
            perror("Error: cannot open server FIFO");
            exit(EXIT_FAILURE);
        }

        char buf[BUFFER_SIZE];
        if (read(fd, buf, BUFFER_SIZE) > 0) {
            printf("---CLIENT CONNECTED: %s---\n", buf);

            int fd2 = open(buf, O_RDWR);
            if (fd2 < 0) {
                perror("Error: cannot open client FIFO");
                close(fd);
                continue;
            }

            char command[BUFFER_SIZE];
            while (read(fd2, command, BUFFER_SIZE) > 0) {
                printf("Received command: %s\n", command);

                FILE *command_output = popen(command, "r");
                if (command_output == NULL) {
                    perror("Error: cannot execute command");
                    write(fd2, "Error: cannot execute command\n", 30);
                    continue;
                }

                char output[BUFFER_SIZE];
                while (fgets(output, BUFFER_SIZE, command_output) != NULL) {
                    write(fd2, output, strlen(output));
                }

                pclose(command_output);
                write(fd2, "The end of the command\n", 23); 
            }

            close(fd2);
        }

        close(fd);
    }

    unlink(SERVER_FIFO);
    return 0;
}
