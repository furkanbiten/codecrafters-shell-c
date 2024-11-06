#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int read_dir(char* dir_path, char* exes[], char* locs[])
{

    DIR* d;
    struct dirent* file;
    char* token;
    int count = 0;
    while ((token = strsep(&dir_path, ":"))) {

        d = opendir(token);
        if (d) {
            while ((file = readdir(d)) != NULL) {
                if (!strncmp(file->d_name, ".", 1) || strncmp(file->d_name, "..", 2)) {
                    exes[count] = strdup(file->d_name);
                    locs[count] = strdup(token);
                    // exes[count] = file->d_name;
                    // locs[count] = token;
                    // printf("%s \t %s\n", exes[count], locs[count]);
                    count++;
                }

                if (count >= 500) {
                    printf("Reached maximum limit for commands and locs\n");
                    break;
                }
            }
            closedir(d);
        }
    }
    return count;
}

bool find_commands(char* commands[], int com_count, char* locs[], char* input)
{
    for (int i = 0; i < com_count; i++) {
        if (!strcmp(commands[i], input + 5)) {
            printf("%s is %s/%s\n", input + 5, locs[i], input + 5);
            return true;
        }
    }
    // printf("Returning false");
    return false;
}

int main(int argc, char* argv[])
{
    char* path = getenv("PATH");
    char* commands[500];
    char* locs[500];
    int len = read_dir(path, commands, locs);

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

            } 
 
            else {
                bool found = find_commands(commands, len, locs, input);
                if (!found) {
                    printf("%s: not found\n", input + 5);
                }
            }
        }

        else if (!strncmp(input, "echo ", 5)) {
            printf("%s\n", input + 5);
        } else {
            printf("%s: command not found\n", input);
        }
    }
    return 0;
}
