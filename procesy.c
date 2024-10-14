#include <stdio.h>
#include <unistd.h>
int main(){
    printf ("Begin"); // Difference with '\n' - flush, wymusza
    fork();
    printf ("End");
    return 0;
}