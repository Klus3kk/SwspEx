#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void texty(int signo) {
    printf("Signal: %d\n", signo);
}

int main(int argc, char* argv[]) {
    for(int i = 1; i < 31; i++) { // Total number of signals: 31
        signal(i, texty);
    }
    while(1);
}