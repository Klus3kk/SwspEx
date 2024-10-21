#include <stdio.h>
#include <unistd.h>
int main(){ // We can't say which process will be first
    fork();
    printf("Hi\n");
    fork();
    printf("Ha\n");
    fork();
    wait(NULL); // Pochodne procesy czekaja
    printf("Ho\n");
    exit(7); // We can also use kill(pid, signum)
    
    return 0;
}