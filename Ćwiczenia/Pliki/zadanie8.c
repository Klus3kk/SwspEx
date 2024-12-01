#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int fd;
    if (argc == 2) {
        fd = open(argv[1], O_RDWR);
        if (fd == -1) {
            perror("Error opening file");
            return 1;
        }
    } else {
        fd = STDIN_FILENO;
    }

    char buf[1024];
    int n;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < n; i++) {
            buf[i] = toupper((unsigned char)buf[i]);
        }
        write(STDOUT_FILENO, buf, n);
    }

    if (fd != STDIN_FILENO) {
        close(fd);  
    }

    return 0;
}
