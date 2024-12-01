#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>


// Zombi is the parent alone
int main(int argc, char* argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process: %d\n", getpid());
        exit(0); 
    } else if (pid > 0) {
        printf("Parent process: %d\n", getpid());
        sleep(3); // Zombi state
        wait(NULL); 
    } 

    return 0;
}
