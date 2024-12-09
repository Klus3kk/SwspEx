#include <stdio.h>
#include <unistd.h>
#include <signal.h>




int main(int argc, char* argv[]) {
    unsigned int i;
    int num = 0;
    printf("Give me a number, round, cool one: ");
    scanf("%d",&i);
    printf("So...your number is %d? Coool\n", i);
    alarm(i);
    printf("Let's count together!\n");
    while(1) {
        printf("%d\n", num);
        num += 1;
        sleep(1);
    }
    return 0;
}