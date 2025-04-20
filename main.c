#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>



#define MAX_INPUT 1024
#define MAX_ARGS 64

int main(void) {
    
    char input[MAX_INPUT];
    char *args[MAX_INPUT];
    char *token;
    int i;
    pid_t pid;

    while (1)
    {
        printf("$ ");

        if(fgets(input, MAX_INPUT, stdin) == NULL) 
        {
            printf("\n");
            break; 
        }

        input[strcspn(input, "\n")] = 0; 
        
        token = strtok(input, " ");
        i = 0;
        while (token != NULL && i < MAX_INPUT-1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; 

        pid = fork();
        if (pid == 0)
        {
            execvp(args[0],args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0){
            wait(NULL);
        }else{
            perror("fork");
        }
    }
    

    return 0;
}
