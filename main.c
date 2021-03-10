  
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int		main(void)
{
	pid_t	pid;
	char	comando[64];
	printf("minishell: ");
	memset(comando, '\0', 64);	// empty's string
	scanf("%s", comando);		// reads from keybord a command
	while (strcmp(comando, "exit")) // compares the command with "exit"
	{
		pid = fork();	//creates a process
		if (pid == 0)	//child process
		{
			execlp(comando, comando, NULL);
			printf("comando no valido\n");
			exit(0);
		}
		else
		{
			if (pid > 0) //parent process
			{
				waitpid(pid, 0, 0);
				printf("minishell: ");
				memset(comando, '\0', 64);	// empty's string
				scanf("%s", comando);	// reads from keybord a command
			}
			else
				perror("Error Fork\n");
		}
	}
	exit(0);
}
