#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

// Orphan is the child alone

int main(int argc, char* argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process (PID: %d) sleeping...\n", getpid());
        sleep(3); // Orphan state
        printf("Child process (PID: %d) waking up, parent is gone.\n", getpid());
    } else if (pid > 0) {
        printf("Parent process (PID: %d) exiting...\n", getpid());
        exit(0); 
    } 

    return 0;
}
