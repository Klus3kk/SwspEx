#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    struct stat buffer;
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    int fd = open(argv[1], O_RDWR, 0666);
    int status = fstat(fd, &buffer);
    printf("%d", status);
    return 0;
}