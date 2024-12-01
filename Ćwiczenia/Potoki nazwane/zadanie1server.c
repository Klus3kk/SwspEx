#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_NAME "server_fifo"
#define BUF_SIZE 100

int main() {
    int fd;
    char buf[BUF_SIZE];

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    printf("=== Oczekiwanie na klienta ===\n");

    fd = open(FIFO_NAME, O_RDONLY);
    if(fd == -1) {
        perror("open");
        exit(1);
    }

    int bytes_read = read(fd, buf, BUF_SIZE - 1);
    if (bytes_read > 0) {
        buf[bytes_read] = '\0';
        printf("Server: %s\n", buf);
    }
    
    close(fd);
    unlink(FIFO_NAME);

    return 0;
}