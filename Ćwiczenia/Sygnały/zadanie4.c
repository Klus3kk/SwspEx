#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void handler(int signo) {}

void sleep2(unsigned int num) {
    signal(SIGALRM, handler);
    alarm(num);
    pause();
    signal(SIGALRM, SIG_DFL);
}

int main(int argc, char* argv[]) {
    unsigned int i;
    printf("Give me a number, round, cool one, it's for this NEW sleep function!\n");
    scanf("%u",&i);
    printf("Sleep well :)\n");
    sleep2(i);
    printf("Wake up, you lazybun! Rise and shine!\n");
    
}