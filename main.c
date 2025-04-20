#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

// Built-in function declarations
void shell_pwd();
void shell_cd(char *path);

int main(void)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    char *token;
    int i;

    while (1)
    {
        printf("$ ");
        if (fgets(input, MAX_INPUT, stdin) == NULL)
        {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;

        token = strtok(input, " ");
        i = 0;
        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }
        else if (strcmp(args[0], "pwd") == 0)
        {
            shell_pwd();
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            shell_cd(args[1]);
        }
        else
        {
            printf("Command not found: %s\n", args[0]);
        }
    }

    return 0;
}

void shell_pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
}

void shell_cd(char *path)
{
    if (path == NULL)
        path = getenv("HOME");

    if (chdir(path) != 0)
        perror("cd");
}
