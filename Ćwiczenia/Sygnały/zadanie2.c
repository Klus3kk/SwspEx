#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void (*f)(); 

int main() {
    f = signal(SIGINT, SIG_IGN);
    printf("SIGINT (Ctrl+C) ignored!");

    signal(SIGINT, f);

}
