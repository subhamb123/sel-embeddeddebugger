#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int readFile(FILE* read) {
	char c = fgetc(read);
	while (c != EOF) {
		printf("%c", c);
		c = fgetc(read);
	}

	putchar('\n');
	putchar('\n');
}

int main() {
	int choice = 0;

	while(choice != 3) {
		printf("1. Show data after an exception\n");
		printf("2. Show data after snapshot gets reloaded\n");
		printf("3. Exit\n");
		printf("Your choice: ");
		scanf("%d", &choice);
		putchar('\n');

		if (choice == 1) {
			FILE* read = fopen("stack.txt", "r");
			readFile(read);
			fclose(read);
		}
		else if (choice == 2) {
			FILE* read = fopen("tasks.txt", "r");
			readFile(read);
			fclose(read);
		}
	}
}