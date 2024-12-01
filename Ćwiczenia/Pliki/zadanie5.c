#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Too many/less arguments provided. Usage: ./zadanie5 <file>\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file\n");
        return 1;
    }

    off_t fileSize = lseek(fd, 0, SEEK_END);
    if (fileSize == -1) {
        perror("Error getting file size\n");
        close(fd);
        return 1;
    }

    char buf[1];  

    for (off_t i = fileSize - 1; i >= 0; i--) {
        if (lseek(fd, i, SEEK_SET) == -1) {
            perror("Error seeking in file\n");
            close(fd);
            return 1;
        }

        if (read(fd, buf, 1) != 1) {
            perror("Error reading file\n");
            close(fd);
            return 1;
        }

        write(STDOUT_FILENO, buf, 1);  
    }

    close(fd);
    return 0;
}
