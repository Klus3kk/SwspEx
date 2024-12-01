#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    int fd;
    int wordCount = 0;
    if (argc == 2) {
        fd = open(argv[1], O_RDWR);
        if (fd == -1) {
            perror("Error opening file");
            return 1;
        }
    } else {
        fd = STDIN_FILENO;
    }


    char buffer;
    int inWord = 0;  
    while (read(fd, &buffer, 1) == 1) {
        if (isalnum(buffer) || buffer == '_') {  
            if (!inWord) {      
                inWord = 1;
                wordCount++;
            }
        } else { 
            inWord = 0;
        }
        if(buffer == '$') {
            break;
        }
    }

    if (fd != STDIN_FILENO) {
        close(fd);  
    }

    printf("Number of words: %d\n", wordCount);
    return 0;
}
