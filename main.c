#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

void shell_pwd();
void shell_cd(char *path);
void shell_ls();
void shell_echo(char *args[]);

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

        // Tokenize input into args
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

        // Command execution
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
        else if (strcmp(args[0], "ls") == 0)
        {
            shell_ls();
        }
        else if (strcmp(args[0], "echo") == 0)
        {
            shell_echo(args);
        }
        else
        {
            printf("Command not found: %s\n", args[0]);
        }
    }

    return 0;
}

// Built-in: pwd
void shell_pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
}

// Built-in: cd
void shell_cd(char *path)
{
    if (path == NULL)
        path = getenv("HOME");

    if (chdir(path) != 0)
        perror("cd");
}

// Built-in: ls
void shell_ls()
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL)
    {
        perror("ls");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.') 
            printf("%s  ", entry->d_name);
    }

    printf("\n");
    closedir(dir);
}
void shell_echo(char *args[]) {
    if (args[1] == NULL) {
        printf("echo: missing operand\n");
        return;
    }
    while (args[1] != NULL) {
        printf("%s ", args[1]);
        args++;
    }
    printf("\n");
}
