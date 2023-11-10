nclude <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CMD_LEN 128
#define HISTORY_COUNT 20

int main() {

	char cmd[MAX_CMD_LEN];
	char* args[2];
	pid_t pid;
	int status;

	while(1) {

	// Print command prompt

	printf("simple_shell> ");
	if(fgets(cmd, sizeof(cmd), stdin) == NULL)
	{ 
		// end-of-file
		printf("\n");
		exit(0);
	}

    // Remove trailing newline

	if (cmd[strlen(cmd)-1] == '\n') 
	{
		cmd[strlen(cmd)-1] = '\0';
	}

	args[0] = cmd; // the command itself
	args[1] = NULL; // no additional arguments

	if((pid = fork()) < 0)
	{
		printf("Error: Cannot create new process.\n");
		continue;
	}

	if(pid == 0)
	{
		// Replace current process image with new program
		execve(args[0], args, NULL);

		// execve() only returns on error
		perror("execve");
		exit(1);
	} else {

		// Parent process waits for child to finish
		wait(&status);

		if (WIFEXITED(status) && (WEXITSTATUS(status) != 0))
		{
			printf("Error: command not found: %s\n", cmd);
		}
	}
	}

	return 0;
}
