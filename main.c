#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stddef.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

typedef struct Variable {
    char *name;
    char *value;
    struct Variable *next;
} Variable;

Variable *variables = NULL;

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
void shell_set(char **args);
void shell_get(char **args);

cmd builtins[] = {
    {"exit", shell_exit, "Exit the shell"},
    {"pwd", shell_pwd, "Print current directory"},
    {"echo", shell_echo, "Print arguments"},
    {"help", shell_help, "Show this help message"},
    {"set", shell_set, "Set variable (name=value)"},
    {"get", shell_get, "Get variable value"},
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
        char *output_file = NULL;
        char *input_file = NULL;
        int i = 0;
        char *token = strtok(input, " ");

        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        for (int j = 0; args[j]; j++) {
            if (strcmp(args[j], ">") == 0) {
                output_file = args[j+1];
                args[j] = NULL;
                break;
            }
            if (strcmp(args[j], "<") == 0) {
                input_file = args[j+1];
                args[j] = NULL;
                break;
            }
        }

        if (args[0] == NULL) continue;

        int found = 0;
        for (int j = 0; j < num_builtins; j++) {
            if (strcmp(args[0], builtins[j].name) == 0) {
                if (output_file) freopen(output_file, "w", stdout);
                if (input_file) freopen(input_file, "r", stdin);

                builtins[j].func(args);

                if (output_file || input_file) {
                    freopen("/dev/tty", "r", stdin);
                    freopen("/dev/tty", "w", stdout);
                }
                found = 1;
                break;
            }
        }

        if (!found) printf("Command not found: %s\n", args[0]);
    }
    return 0;
}

void shell_exit(char **args) { exit(0); }

void shell_pwd(char **args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s\n", cwd);
    else perror("pwd");
}

void shell_echo(char **args) {
    if (!args[1]) {
        printf("echo: missing operand\n");
        return;
    }
    for (int i = 1; args[i]; i++) {
        if (args[i][0] == '$') {
            char *name = args[i]+1;
            Variable *var = variables;
            while (var) {
                if (strcmp(var->name, name) == 0) {
                    printf("%s ", var->value);
                    break;
                }
                var = var->next;
            }
        } else {
            printf("%s ", args[i]);
        }
    }
    printf("\n");
}

void shell_help(char **args) {
    printf("Available commands:\n");
    for (int i = 0; i < num_builtins; i++) {
        printf("  %-8s\t%s\n", builtins[i].name, builtins[i].description);
    }
}

void shell_set(char **args) {
    if (!args[1]) {
        printf("set: missing variable\n");
        return;
    }
    char *name = strtok(args[1], "=");
    char *value = strtok(NULL, "=");
    if (!name || !value) {
        printf("set: invalid format\n");
        return;
    }
    Variable *var = variables;
    while (var) {
        if (strcmp(var->name, name) == 0) {
            free(var->value);
            var->value = strdup(value);
            return;
        }
        var = var->next;
    }
    Variable *new_var = malloc(sizeof(Variable));
    new_var->name = strdup(name);
    new_var->value = strdup(value);
    new_var->next = variables;
    variables = new_var;
}

void shell_get(char **args) {
    if (!args[1]) {
        printf("get: missing variable\n");
        return;
    }
    Variable *var = variables;
    while (var) {
        if (strcmp(var->name, args[1]) == 0) {
            printf("%s=%s\n", var->name, var->value);
            return;
        }
        var = var->next;
    }
    printf("Variable not found: %s\n", args[1]);
}