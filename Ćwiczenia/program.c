#include <stdio.h>

int main(int argc, char* argv[]) {
	if(argc == 1) {
		printf("Please write some arguments :) \n");
		return 0;
	}
	printf("Hi there! Here are your arguments: \n");
	for (int i = 1; i < argc; i++) {
		printf("[%d]: %s  \n", i, argv[i]);
	}
	return 0;
}
