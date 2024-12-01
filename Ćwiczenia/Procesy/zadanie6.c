#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
    pid_t pid;
    int i;
    for (i = 0; i < 3; i++) {
        pid = fork();

        if (pid == 0) {
            // Child process
            printf("Child process %d (PID: %d) exiting...\n", i + 1, getpid());
            exit(0); // Zombi
        } else if (pid > 0) {
            // Parent process
            printf("Parent created child process %d (PID: %d)\n", i + 1, pid);
        }
    }
    sleep(3); // Child will be in zombie mode

    printf("Parent process is collecting zombie processes...\n");
    
    // Removing the zombies
    for (i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("All zombie processes have been collected.\n");

    return 0;
}
