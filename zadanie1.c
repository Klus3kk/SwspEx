#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Too many arguments! \n");
        return 0;
    }
    int fd = open(argv[1], O_RDWR, 0666);
    int fd2 = open(argv[2], O_RDWR|O_TRUNC, 0666);

    char buf[1000];
    while(read(fd,buf,10) > 0) {
        write(fd2,buf,10);
    }
}