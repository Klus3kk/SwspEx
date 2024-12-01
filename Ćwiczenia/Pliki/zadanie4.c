#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Too many/less arguments provided. Usage: ./zadanie4 <file>\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file\n");
        return 1;
    }

    char buf[1024];
    int maxLineLength = 0; 
    int currentLineLength = 0; 
    int n;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < n; i++) {
            if (buf[i] == '\n') {
                if (currentLineLength > maxLineLength) {
                    maxLineLength = currentLineLength;
                }
                currentLineLength = 0; 
            } else {
                currentLineLength++;  
            }
        }
    }

    if (currentLineLength > maxLineLength) {
        maxLineLength = currentLineLength;
    }

    close(fd);

    printf("The longest line has %d characters.\n", maxLineLength);
    return 0;
}
