#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 1024
#define MAX_ARGS 10

extern char **environ;

void env(void) {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t lineSize;
    char *argv[MAX_ARGS + 2];
    pid_t child_pid;
    int child_status;
    char *token;
    int i;

    while (1) {
        printf("($) ");
        lineSize = getline(&line, &bufsize, stdin);

        if (lineSize == -1) {
            if (feof(stdin)) {
                /* reached (Ctrl+D), exit gracefully */
                free(line);
                exit(EXIT_SUCCESS);
            } else {
                perror("Error");
                continue;
            }
        }
        line[lineSize - 1] = '\0'; /* Remove the newline character */

        token = strtok(line, " "); /* Tokenize the input string */

        for (i = 0; i < MAX_ARGS && (token != NULL); i++) {
            argv[i] = token;
            token = strtok(NULL, " ");
        }
        argv[i] = NULL; /* Set the last element to NULL */

        /* Implement the env built-in command */
        if (argv[0] != NULL && strcmp(argv[0], "env") == 0) {
            char **current;
            for (current = environ; *current != NULL; current++) {
                printf("%s\n", *current);
            }
            continue; /* Return to the top of the loop without creating a new process */
        }

        /* Implement the exit built-in command */
        if (argv[0] != NULL && strcmp(argv[0], "exit") == 0) {
            free(line);
            exit(EXIT_SUCCESS);
        }

        child_pid = fork();
        if (child_pid == -1) {
            perror("Error");
            continue;
        }
        if (child_pid == 0) {
            execvp(argv[0], argv); /* Use execvp to search for the command in PATH */
            perror("Error");
            _exit(1);
        } else {
            wait(&child_status);
            if (WIFEXITED(child_status) && (WEXITSTATUS(child_status) != 0)) {
                printf("Error: command not found: %s\n", argv[0]);
            }
        }
    }

    free(line);
}

