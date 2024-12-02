#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

void create_fifo(const char *fifo_name) {
    if(mkfifo(fifo_name, 0666) == -1) {
        perror("Error: can't create FIFO");
        exit(EXIT_FAILURE);
    }
}

void remove_fifo(const char *fifo_name) {
    if (unlink(fifo_name) == -1) {
        perror("Error: can't remove FIFO");
    }
}

int main() {
    int num_process;
    printf("Number of processes in the ring: ");
    scanf("%d", &num_process);

    if (num_process < 2) {
        fprintf(stderr, "The number of processes must be bigger than 1.\n");
        exit(EXIT_FAILURE);
    }

    char fifo_names[num_process][BUFFER_SIZE];
    for (int i = 0; i < num_process; i++) {
        snprintf(fifo_names[i], BUFFER_SIZE, "fifo_%d", i);
    }

    for (int i = 0; i < num_process; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Error: can't fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            char message[BUFFER_SIZE];
            int fd_read = open(fifo_names[i], O_RDONLY);
            int fd_write = open(fifo_names[(i + 1) % num_process], O_WRONLY);

            if (fd_read == -1 || fd_write == -1) {
                perror("Error: can't open FIFO");
                exit(EXIT_FAILURE);
            }

            while (1) {
                if (read(fd_read, message, BUFFER_SIZE) > 0) {
                    printf("Process %d (%d): %s\n", i, getpid(), message);

                    char appended_message[BUFFER_SIZE];
                    snprintf(appended_message, BUFFER_SIZE, "%s -> %d", message, getpid());

                    write(fd_write, appended_message, strlen(appended_message) + 1);

                }
            }
            close(fd_read);
            close(fd_write);
            exit(EXIT_SUCCESS);
        }
    }
    char initial_message[BUFFER_SIZE] = "Start";
    int fd_write = open(fifo_names[0], O_WRONLY);
    if (fd_write == -1) {
        perror("Error: can't open FIFO to initialization");
        exit(EXIT_FAILURE);
    }
    write(fd_write, initial_message, strlen(initial_message) + 1);
    close(fd_write);

    for (int i = 0; i < num_process; i++) {
        wait(NULL);
    }

    for (int i = 0; i < num_process; i++) {
        remove_fifo(fifo_names[i]);
    }

    return 0;
}