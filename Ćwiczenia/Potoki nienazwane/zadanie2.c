#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    int fd[2];
    pid_t pid1, pid2;
    char buffer[1024];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        return 1;
    } else if (pid1 == 0) {
        close(fd[0]);  
        write(fd[1], "Hallo", 5); 
        close(fd[1]); 
        return 0;
    } 

    pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        return 1;
    } else if (pid2 == 0) {
        close(fd[1]);  

        read(fd[0], buffer, sizeof(buffer)); 
        printf("Odczytano z potoku: %s\n", buffer); 
        close(fd[0]);  
        return 0;
    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}
