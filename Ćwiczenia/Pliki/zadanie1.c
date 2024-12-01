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
    int fd2 = open(argv[2], O_RDWR|O_TRUNC|O_CREAT, 0666);

    if(fd == -1 || fd2 == -1) {
        perror("Error! File does not exist!\n");
        return 0;
    }
    ssize_t n;
    char buf[1000];
    while(n = read(fd,buf,1) > 0) {
        write(fd2,buf,n);
    }
    close(fd);
    close(fd2);
}