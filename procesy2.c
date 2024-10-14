#include <stdio.h>
#include <unistd.h>
int main(){ // We can't say which process will be first
    fork();
    printf("Hi\n");
    fork();
    printf("Ha\n");
    fork();
    printf("Ho\n");
    return 0;
}