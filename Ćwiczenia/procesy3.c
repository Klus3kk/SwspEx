#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int status = 4;
    if(fork() != 0) {
        wait(&status);
    } else {
        exit(1);
        // kill(1,&status);
    }
    printf("%x\n", status);
    printf("%04x\n", status);

    // exit(), pozniej kill()
    return 0;
}