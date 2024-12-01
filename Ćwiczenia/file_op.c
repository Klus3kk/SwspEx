#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int fd = open("idk.c", O_RDWR|O_CREAT, 0644);

    char buf[100];
    while(read(fd, buf, 10) > 0) { // fd -> buf
        write(1, buf, 10); // fd <- buf
    }

    return 0;
}