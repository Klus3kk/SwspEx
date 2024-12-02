#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define SERVER_FIFO "server_fifo"
#define BUFFER_SIZE 256

int main() {
    unlink(SERVER_FIFO);
    mkfifo(SERVER_FIFO, 0666);
    printf("---SERVER ACTIVATED---\n");

    int fd;
    char buf[BUFFER_SIZE];
    while (1) {
        fd = open(SERVER_FIFO, O_RDONLY);
        if (fd < 0) {
            perror("Error: can't open the server");
            exit(EXIT_FAILURE);
        }

        if (read(fd, buf, BUFFER_SIZE) > 0) {
            printf("---CLIENT RECEIVED---\n---%s---\n", buf);

            FILE *output = popen("ls", "r");
            if (output == NULL) {
                perror("Error: can't make a command");
                close(fd);
                continue;
            }

            int fd2 = open(buf, O_WRONLY);
            if (fd2 < 0) {
                perror("Error: can't open a client");
                pclose(output);
                close(fd);
                continue;
            }

            char buf2[BUFFER_SIZE];
            while (fgets(buf2, BUFFER_SIZE, output) != NULL) {
                write(fd2, buf2, strlen(buf2));
            }

            close(fd2);
            pclose(output);
        }
        close(fd);
    }

    unlink(SERVER_FIFO);
    return 0;
}
