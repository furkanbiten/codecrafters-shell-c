#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int is_executable(const char* path) { return access(path, X_OK) == 0; }

char* find_in_path(char* command)
{
    char* path = getenv("PATH");
    if (path == NULL) {
        return NULL;
    }
    char* path_copy = strdup(path);
    char* dir = strtok(path_copy, ":");
    static char tokenized_path[1024];
    while (dir != NULL) {

        snprintf(tokenized_path, sizeof(tokenized_path), "%s/%s", dir, command);

        if (is_executable(tokenized_path)) {

            free(path_copy);
            char* result = strdup(tokenized_path);
            return result;
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);

    return NULL;
}

void type_command(char* input)
{
    char* cmd = input + 5;

    if (strncmp(cmd, "cd", 2) == 0 || strncmp(cmd, "echo", 4) == 0 || strncmp(cmd, "pwd", 3) == 0 || strncmp(cmd, "exit", 4) == 0 || strncmp(cmd, "type", 4) == 0) {
        printf("%s is a shell builtin\n", cmd);
    } else {
        char* cmd_path = find_in_path(cmd);
        if (cmd_path) {
            printf("%s is %s\n", cmd, cmd_path);
        } else {
            printf("%s: not found\n", cmd);
        }
    }
}

bool check_others(char* input){
    char* input_copy = strdup(input);
    char* cmd = strtok(input_copy, " ");
    char* args = strtok(NULL, "");
    char* cmd_path = find_in_path(cmd);

    if (cmd_path) {
        char temp_buffer[1024];
        sprintf(temp_buffer, "%s %s", cmd_path, args);

        system(temp_buffer);
        free(input_copy);
        return true;
    }
    return false;
}

int main(int argc, char* argv[])
{

    while (1) {
        printf("$ ");
        fflush(stdout);

        // Wait for user input
        char input[100];
        fgets(input, 100, stdin);
        input[strlen(input) - 1] = '\0';
        if (strlen(input) == 0) {
            continue;
        }

        if (strncmp(input, "exit ", 5) == 0) {
            exit(0);
        }

        if (strncmp(input, "echo ", 5) == 0) {
            printf("%s\n", input + 5);
            continue;
        }

        if (strncmp(input, "pwd", 3) == 0) {
            system("pwd");
            continue;
        }

        if (strncmp(input, "type ", 5) == 0) {
            type_command(input);
            continue;
        }

        bool found_cmd = check_others(input);
        if (found_cmd){
            continue;
        }

        if (strncmp(input, "cd ", 3) == 0) {
            char* input_copy = strdup(input);
            char* cmd = strtok(input_copy, " ");
            char* args = strtok(NULL, " ");
            if (access(args, F_OK) == 0){
                chdir(args);
            } else{
                printf("cd: %s: No such file or directory\n", args);
            }
            continue;
        }

        printf("%s: command not found\n", input);
    }
    return 0;
}
