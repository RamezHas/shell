#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

typedef void (*cmdFunc)(char **args);

typedef struct {
    char *name;
    cmdFunc func;
    char *description;
} cmd;

void shell_exit(char **args);
void shell_pwd(char **args);
void shell_echo(char **args);
void shell_help(char **args);

cmd builtins[] = {
    {"exit", shell_exit, "Exit the shell"},
    {"pwd", shell_pwd, "Print current directory"},
    {"echo", shell_echo, "Print arguments"},
    {"help", shell_help, "Show this help message"},
};

int num_builtins = sizeof(builtins) / sizeof(cmd);

int main(void) {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1) {
        printf("$ ");
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;

        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) continue;

        int found = 0;
        for (int j = 0; j < num_builtins; j++) {
            if (strcmp(args[0], builtins[j].name) == 0) {
                builtins[j].func(args);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Command not found: %s\n", args[0]);
        }
    }

    return 0;
}

void shell_exit(char **args) {
    exit(0);
}

void shell_pwd(char **args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
}

void shell_echo(char **args) {
    if (!args[1]) {
        printf("echo: missing operand\n");
        return;
    }
    for (int i = 1; args[i]; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

void shell_help(char **args) {
    printf("Available commands:\n");
    for (int i = 0; i < num_builtins; i++) {
        printf("  %-8s\t%s\n", builtins[i].name, builtins[i].description);
    }
}