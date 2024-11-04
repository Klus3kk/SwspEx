#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int fd1[2], fd2[2], fd3[2];
    pid_t pid1, pid2, pid3, pid4;
    int numbers[4] = {1, 2, 3, 4};
    
    if (pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1) {
        perror("pipe");
        return 1;
    }

    pid1 = fork();
    if (pid1 == 0) {
        close(fd1[0]);
        write(fd1[1], numbers, sizeof(numbers));
        close(fd1[1]);
        return 0;
    }

    pid2 = fork();
    if (pid2 == 0) {
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0], numbers, sizeof(numbers));
        for (int i = 0; i < 4; i++) {
            numbers[i] += 1;
        }
        write(fd2[1], numbers, sizeof(numbers));
        close(fd1[0]);
        close(fd2[1]);
        return 0;
    }

    pid3 = fork();
    if (pid3 == 0) {
        close(fd2[1]);
        close(fd3[0]);
        read(fd2[0], numbers, sizeof(numbers));
        for (int i = 0; i < 4; i++) {
            numbers[i] += 1;
        }
        write(fd3[1], numbers, sizeof(numbers));
        close(fd2[0]);
        close(fd3[1]);
        return 0;
    }

    pid4 = fork();
    if (pid4 == 0) {
        close(fd3[1]);
        read(fd3[0], numbers, sizeof(numbers));
        for (int i = 0; i < 4; i++) {
            numbers[i] += 1;
        }
        printf("Ostateczne liczby: ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        close(fd3[0]);
        return 0;
    }

    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    close(fd3[0]);
    close(fd3[1]);

    return 0;
}
