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
    char buf[BUFFER_SIZE];
    snprintf(buf, BUFFER_SIZE, "client_fifo_%d", getpid());

    if (mkfifo(buf, 0666) < 0) {
        perror("Error: can't create client FIFO");
        exit(EXIT_FAILURE);
    }

    int fd = open(SERVER_FIFO, O_WRONLY);
    if (fd < 0) {
        perror("Error: can't open the server");
        unlink(buf);
        exit(EXIT_FAILURE);
    }

    write(fd, buf, strlen(buf) + 1);
    close(fd);

    int fd2 = open(buf, O_RDONLY);
    if (fd2 < 0) {
        perror("Error: can't open client FIFO");
        unlink(buf);
        exit(EXIT_FAILURE);
    }

    printf("Ls results:\n");
    char buf2[BUFFER_SIZE];
    while (read(fd2, buf2, BUFFER_SIZE) > 0) {
        printf("%s", buf2);
    }

    close(fd2);
    unlink(buf);
    unlink(SERVER_FIFO);
    return 0;
}
