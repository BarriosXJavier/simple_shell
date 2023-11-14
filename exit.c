#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define MAX_ARGS 10

void custom_exit(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t lineSize;
    char *argv[MAX_ARGS + 2]; /* +2 to include space for the command and NULL terminator */
    pid_t child_pid;
    int child_status;
    char *path;
    char *token;
    int i = 0;
    char *path_component; 

    while (1)
    {
        printf("($) ");
        lineSize = getline(&line, &bufsize, stdin);

        if (lineSize == -1)
        {
            perror("Error");
            continue;
        }

        line[lineSize - 1] = '\0'; /* Remove the newline character */

        token = strtok(line, " "); /* Tokenize the input string */
        while (token != NULL && i < MAX_ARGS)
        {
            argv[i] = token;
            token = strtok(NULL, " ");
            i++;
        }

        argv[i] = NULL; /* Set the last element to NULL as required by execve */

        if (argv[0] != NULL && strcmp(argv[0], "exit") == 0)
        {
            free(line);
            exit(EXIT_SUCCESS);
        }

        /* Check if the command exists in the current directory or in the PATH environment variable */
        path = getenv("PATH");

        if (path == NULL)
        {
            perror("Error: PATH environment variable not set");
            continue;
        }

        for (path_component = path; *path_component != '\0'; path_component++)
        {
            if (strcmp(path_component, argv[0]) == 0)
            {
                /* The command exists in the current directory, so execute it directly */
                execvp(argv[0], argv);
                break;
            }
        }

        /* If the command doesn't exist in the current directory or the PATH environment variable,
         * try executing it through fork and execve */
        child_pid = fork();

        if (child_pid == -1)
        {
            perror("Error");
            continue;
        }

        if (child_pid == 0)
        {
            /* Execute the command via fork and execve */
            execvp(argv[0], argv);
            perror("Error");
            _exit(1);
        }
        else
        {
            wait(&child_status);
            if (WIFEXITED(child_status) && (WEXITSTATUS(child_status) != 0))
            {
                printf("Error: command not found: %s\n", argv[0]);
            }
        }

        i = 0; /* Reset index for the next iteration */
    }

    free(line);
}
