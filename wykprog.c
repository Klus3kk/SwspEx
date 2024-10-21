#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
    printf("Begin\n");
    sleep(3);

    if (fork() == 0) {
        execl("/bin/ls", "ls", "-a", NULL);
        exit(1); 
    } else {
        wait(NULL); 
    }

    printf("Finish!\n");

    return 0;
}
