#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

int main(void) {
    
    char input[MAX_INPUT];
    char *args[MAX_INPUT];
    char *token;
    int i;

    while (1)
    {
        printf("$ ");

        if(fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break; 
        }

        input[strcspn(input, "\n")] = 0; // Remove newline character
        
        token = strtok(input, " ");
        i = 0;
        while (token != NULL && i < MAX_INPUT-1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the array of arguments

        for (int j = 0; j < i; j++)
        {
            printf("args[%d]: %s\n", j, args[j]);
        }
        
    }
    

    return 0;
}
