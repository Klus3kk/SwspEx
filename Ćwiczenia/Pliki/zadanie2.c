#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("You didn't give any files names\n");
        return 0;
    }

    for(int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDWR, 0666);
        char buf[1000];
        if(fd == -1) {
            printf("There is no such file as %s existing!\n", argv[i]);
        } else {
            int n = lseek(fd, 0, SEEK_END);
            printf("%s is %d long\n", argv[i], n);
        }
        close(fd);
    }
    return 0;
}