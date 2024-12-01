#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <first_file> <second_file>\n", argv[0]);
        return 1;
    }
    int fd1 = open(argv[1], O_RDWR, 0666);
    int fd2 = open(argv[2], O_RDWR, 0666);

    char buf1;
    char buf2;
    while
    return 0;
}