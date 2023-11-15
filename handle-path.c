#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024
#define MAX_ARGS 10

void handle_path(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t lineSize;
	/*+2 space for the cmd & NULL terminator */

	char *argv[MAX_ARGS + 2];
	pid_t child_pid;
	int child_status;
	int i = 0;
	char *token;
	/*Tokenize the input string*/
	token = strtok(line, " ");

    while (1)
    {
        printf("($) ");
        lineSize = getline(&line, &bufsize, stdin);

        if (lineSize == -1)
        {
            perror("Error");
            continue;
        }

        line[lineSize - 1] = '\0';

        while (token != NULL && i < MAX_ARGS)
        {
            argv[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        argv[i] = NULL;

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
    }

    free(line);
}
