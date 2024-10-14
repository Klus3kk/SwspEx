#include <stdio.h>
#include <unistd.h>
int main() {
    if(fork() == 0) { // If 0, then it's potomna sekcja
        // printf("Child\n");
        printf("--------\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        printf("--------\n");
    } else {
        // printf("Parent\n");
        printf("--------\n");
        printf("PPID: %d\n", getppid());
        printf("PID: %d\n", getpid());
        printf("--------\n");
    }

    // printf ("Begin"); // Difference with '\n' - flush, wymusza
    // fork();
    // printf ("End");
    return 0;
}

