#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_NAME "server_fifo"

int main() {
    int fd;
    char *message = "HALLO!";

    printf("=== Klient ===\n");

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
    } else {
        printf("Klient: %s\n", message);
    }

    close(fd);

    return 0;
}
