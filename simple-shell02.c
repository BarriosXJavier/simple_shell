#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 1024
#define MAX_ARGS 10

int main(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t lineSize;
	char *argv[MAX_ARGS+2]; /* +2 to include space for the command and NULL terminator */
	pid_t child_pid;
	int child_status;

	while (1) {
		printf("($) ");
		lineSize = getline(&line, &bufsize, stdin);

		if (lineSize == -1)
		{
			perror("Error");
			continue;
		}

	line[lineSize - 1] = '\0'; // Remove the newline character

	char *token;
	int i = 0;
	token = strtok(line, " "); // Tokenize the input
	while (token != NULL && i < MAX_ARGS) {
		argv[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL; // Set the last element to NULL as required by execve

	child_pid = fork();

	if (child_pid == -1) {
		perror("Error");
		continue;
	}
	if (child_pid == 0) {
		execvp(argv[0], argv); // Use execvp to search for the command in PATH
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
	return (0);
}
