#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int signo) {
    int status;
    pid_t pid = wait(&status);
    if (pid > 0) printf("Proces potomny %d finished\n", pid);
}

void signal_handling() {
    signal(SIGCHLD, handler);

    pid_t pid = fork();
    if (pid == 0) {
        // Proces potomny
        printf("Proces potomny: Working...\n");
        sleep(2);
        printf("Proces potomny: Adios amigos...\n");
        exit(0);
    } else if (pid > 0) {
        // Proces macierzysty
        printf("Proces macierzysty: Waiting for the SIGCHLD.\n");
        pause(); 
    }
}

void signal_ignored() {
    signal(SIGCHLD, SIG_IGN);

    pid_t pid = fork();
    if (pid == 0) {
        printf("Proces potomny: Working...\n");
        sleep(2);
        printf("Proces potomny: Adios amigos...\n");
        exit(0);
    } else if (pid > 0) {
        // Proces macierzysty
        printf("Proces macierzysty: SIGCHLD ignored.\n");
        sleep(3); 
        printf("Proces macierzysty: Didn't get SIGCHLD.\n");
    }
}

int main() {
    printf("1. SIGCHLD handling! \n");
    signal_handling();
    printf("2. SIGCHLD ignored! \n");
    signal_ignored();

    return 0;
}