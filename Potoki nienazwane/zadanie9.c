#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void wait_for_children() {
    while (waitpid(-1, NULL, 0) > 0);
}

void execute_pipeline_1() {
    int fd[2];
    if (pipe(fd) == -1) handle_error("pipe");

    pid_t pid1 = fork();
    if (pid1 == -1) handle_error("fork");

    if (pid1 == 0) {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1) handle_error("dup2");
        close(fd[1]);

        execlp("finger", "finger", NULL);
        handle_error("execlp");
    }

    close(fd[1]);

    pid_t pid2 = fork();
    if (pid2 == -1) handle_error("fork");

    if (pid2 == 0) {
        if (dup2(fd[0], STDIN_FILENO) == -1) handle_error("dup2");
        close(fd[0]);

        execlp("cut", "cut", "-d", " ", "-f1", NULL);
        handle_error("execlp");
    }

    close(fd[0]);
    wait_for_children();
}

void execute_pipeline_2() {
    int fd1[2], fd2[2];
    if (pipe(fd1) == -1 || pipe(fd2) == -1) handle_error("pipe");

    pid_t pid1 = fork();
    if (pid1 == -1) handle_error("fork");

    if (pid1 == 0) {
        close(fd1[0]);
        if (dup2(fd1[1], STDOUT_FILENO) == -1) handle_error("dup2");
        close(fd1[1]);

        execlp("ls", "ls", "-l", NULL);
        handle_error("execlp");
    }

    close(fd1[1]);

    pid_t pid2 = fork();
    if (pid2 == -1) handle_error("fork");

    if (pid2 == 0) {
        if (dup2(fd1[0], STDIN_FILENO) == -1) handle_error("dup2");
        close(fd1[0]);

        close(fd2[0]);
        if (dup2(fd2[1], STDOUT_FILENO) == -1) handle_error("dup2");
        close(fd2[1]);

        execlp("grep", "grep", "^d", NULL);
        handle_error("execlp");
    }

    close(fd1[0]);
    close(fd2[1]);

    pid_t pid3 = fork();
    if (pid3 == -1) handle_error("fork");

    if (pid3 == 0) {
        if (dup2(fd2[0], STDIN_FILENO) == -1) handle_error("dup2");
        close(fd2[0]);

        execlp("more", "more", NULL);
        handle_error("execlp");
    }

    close(fd2[0]);
    wait_for_children();
}

void execute_pipeline_3() {
    int fd1[2], fd2[2], fd3[2], fd4[2];
    if (pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1 || pipe(fd4) == -1) handle_error("pipe");

    pid_t pid1 = fork();
    if (pid1 == -1) handle_error("fork");

    if (pid1 == 0) {
        close(fd1[0]);
        if (dup2(fd1[1], STDOUT_FILENO) == -1) handle_error("dup2");
        close(fd1[1]);

        execlp("ps", "ps", "-ef", NULL);
        handle_error("execlp");
    }

    close(fd1[1]);

    pid_t pid2 = fork();
    if (pid2 == -1) handle_error("fork");

    if (pid2 == 0) {
        if (dup2(fd1[0], STDIN_FILENO) == -1) handle_error("dup2");
        close(fd1[0]);

        close(fd2[0]);
        if (dup2(fd2[1], STDOUT_FILENO) == -1) handle_error("dup2");
        close(fd2[1]);

        execlp("tr", "tr", "-s", " ", ":", NULL);
        handle_error("execlp");
    }

    close(fd1[0]);
    close(fd2[1]);

    pid_t pid3 = fork();
    if (pid3 == -1) handle_error("fork");

    if (pid3 == 0) {
        if (dup2(fd2[0], STDIN_FILENO) == -1) handle_error("dup2");
        close(fd2[0]);

        close(fd3[0]);
        if (dup2(fd3[1], STDOUT_FILENO) == -1) handle_error("dup2");
        close(fd3[1]);

        execlp("cut", "cut", "-d:", "-f1", NULL);
        handle_error("execlp");
    }

    close(fd2[0]);
    close(fd3[1]);

    pid_t pid4 = fork();
    if (pid4 == -1) handle_error("fork");

    if (pid4 == 0) {
        if (dup2(fd3[0], STDIN_FILENO) == -1) handle_error("dup2");
        close(fd3[0]);

        close(fd4[0]);
        if (dup2(fd4[1], STDOUT_FILENO) == -1) handle_error("dup2");
        close(fd4[1]);

        execlp("sort", "sort", NULL);
        handle_error("execlp");
    }

    close(fd3[0]);
    close(fd4[1]);

    pid_t pid5 = fork();
    if (pid5 == -1) handle_error("fork");

    if (pid5 == 0) {
        if (dup2(fd4[0], STDIN_FILENO) == -1) handle_error("dup2");
        close(fd4[0]);

        execlp("uniq", "uniq", "-c", NULL);
        handle_error("execlp");
    }

    close(fd4[0]);
    wait_for_children();
}

void execute_pipeline_4() {
    int fd[2];
    if (pipe(fd) == -1) handle_error("pipe");

    pid_t pid1 = fork();
    if (pid1 == -1) handle_error("fork");

    if (pid1 == 0) {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1) handle_error("dup2");
        close(fd[1]);

        execlp("cat", "cat", "/etc/group", NULL);
        handle_error("execlp");
    }

    close(fd[1]);

    pid_t pid2 = fork();
    if (pid2 == -1) handle_error("fork");

    if (pid2 == 0) {
        int out_fd = open("grupy.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) handle_error("open");

        if (dup2(fd[0], STDIN_FILENO) == -1) handle_error("dup2");
        close(fd[0]);

        if (dup2(out_fd, STDOUT_FILENO) == -1) handle_error("dup2");
        close(out_fd);

        execlp("head", "head", "-5", NULL);
        handle_error("execlp");
    }

    close(fd[0]);
    wait_for_children();
}

int main() {
    int choice;

    printf("Wybierz potok do wykonania:\n");
    printf("1. finger | cut -d' ' -f1\n");
    printf("2. ls -l | grep ^d | more\n");
    printf("3. ps -ef | tr -s ' ' : | cut -d: -f1 | sort | uniq -c | sort -n\n");
    printf("4. cat /etc/group | head -5 > grupy.txt\n");
    printf("Wybór: ");
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Niepoprawny wybór!\n");
        return EXIT_FAILURE;
    }

    switch (choice) {
        case 1:
            execute_pipeline_1();
            break;
        case 2:
            execute_pipeline_2();
            break;
        case 3:
            execute_pipeline_3();
            break;
        case 4:
            execute_pipeline_4();
            break;
        default:
            fprintf(stderr, "Niepoprawny wybór!\n");
            return EXIT_FAILURE;
    }

    return 0;
}
