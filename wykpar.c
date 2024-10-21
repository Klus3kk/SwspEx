#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [arguments]\n", argv[0]);
        return 1;
    }

    struct timeval start, end;
    pid_t pid;
    
    // Pobierz czas początkowy
    gettimeofday(&start, NULL);

    pid = fork();

    if (pid == 0) {
        execvp(argv[1], argv + 1);
        return 1;
    } else if (pid > 0) {
        wait(NULL);
        gettimeofday(&end, NULL);

        double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        printf("Command execution time: %.6f seconds\n", elapsed_time);
    }

    return 0;
}
