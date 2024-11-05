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
        if (!strncmp(input, "exit 0", 100)) {
            exit(0);
        }
        if (!strncmp(input, "echo", 4)) {
            for (int i=5; i<strlen(input); i++){
                printf("%c", input[i]);
            }
            printf("\n");
        } else {
            printf("%s: command not found\n", input);
        }
    }
    return 0;
}
