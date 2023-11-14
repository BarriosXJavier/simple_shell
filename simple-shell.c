#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 1024

void simple_shell(void) {
	char *line = NULL;
	size_t bufsize = 0;
	
	ssize_t lineSize;
	char *argv[] = {"/bin/", NULL, NULL};
	pid_t child_pid;
	int child_status;

	while (1)
	{
		printf("($) ");
		lineSize = getline(&line, &bufsize, stdin);

		if (lineSize == -1) 
		{
			perror("Error");
			continue;
		}

	argv[1] = line;
	argv[1][lineSize - 1] = '\0';

	child_pid = fork();

	if (child_pid == -1) 
	{
		perror("Error");
		continue;
	}
	if (child_pid == 0)
		{
			execve(argv[0], argv, NULL);
			perror("Error");
			_exit(1);
		} else
		
		{
			wait(&child_status);
			if (WIFEXITED(child_status) && (WEXITSTATUS(child_status) != 0)) {
			printf("Error: command not found: %s\n", argv[1]);
		}
		}
	}

	free(line);
}
