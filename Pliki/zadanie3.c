#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        perror("Too many/less arguments provided. ./zadanie3 <file> \n");
        return 0;
    }
    int fd = open(argv[1], O_RDWR, 0666);

    if(fd == -1) {
        perror("No such file exists!\n");
        return 0;
    }
    char buf[1024];
    int n, start = 0;
    while(n = read(fd, buf + start, 1) > 0) {
        if(buf[start] == '\n' || start == 1023) {
            int left = 0;
            int right = start - 1;
            while(left < right) {
                char temp = buf[left];
                buf[left] = buf[right];
                buf[right] = temp;
                left++;
                right--;
            }
            lseek(fd, -(start + 1), SEEK_CUR);
            write(fd, buf, start + 1);

            start = 0;
        } else {
            start++;
        }
    }

    if (start > 0) {
        int left = 0;
        int right = start - 1;
        // Reverse the last line
        while (left < right) {
            char temp = buf[left];
            buf[left] = buf[right];
            buf[right] = temp;
            left++;
            right--;
        }
        lseek(fd, -start, SEEK_CUR);
        write(fd, buf, start); 
    }

    close(fd);
    return 0;
}