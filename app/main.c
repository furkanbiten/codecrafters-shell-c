#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    while (1) {
        printf("$ ");
        fflush(stdout);

        // Wait for user input
        char input[100];
        fgets(input, 100, stdin);
        input[strlen(input) - 1] = '\0';
        if (!strncmp(input, "exit ", 5)) {
            exit(0);
        } else if (!strncmp(input, "type ", 5)) {
            if (!strncmp(input + 5, "echo", 4)) {
                printf("echo is a shell builtin\n");
            } else if (!strncmp(input + 5, "exit", 4)) {
                printf("exit is a shell builtin\n");
            } else if (!strncmp(input + 5, "cat", 4)) {
                printf("cat is /bin/cat\n");
            } else if (!strncmp(input + 5, "type", 4)) {
                printf("type is a shell builtin\n");
            } else {
                printf("%s: not found\n", input+5);
            }

        } else if (!strncmp(input, "echo ", 5)) {
            printf("%s\n", input + 5);
        } else {
            printf("%s: command not found\n", input);
        }
    }
    return 0;
}
