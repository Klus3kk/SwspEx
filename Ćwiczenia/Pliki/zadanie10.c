#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_files...> <output_file>\n", argv[0]);
        return 1;
    }

    int out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (out_fd == -1) {
        perror("Error opening output file");
        return 1;
    }

    char buf[1024];
    int in_fd, n;

    for (int i = 1; i < argc - 1; i++) {
        in_fd = open(argv[i], O_RDONLY);
        if (in_fd == -1) {
            perror("Error opening input file");
            close(out_fd);
            return 1;
        }

        while ((n = read(in_fd, buf, sizeof(buf))) > 0) {
            if (write(out_fd, buf, n) != n) {
                perror("Error writing to output file");
                close(in_fd);
                close(out_fd);
                return 1;
            }
        }

        if (n == -1) {
            perror("Error reading from input file");
            close(in_fd);
            close(out_fd);
            return 1;
        }

        close(in_fd); 
    }

    close(out_fd); 
    return 0;
}
