#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

int		main(void)
{
	pid_t	pid;
	char	comando[64];
	printf("minishell: ");
	memset(comando, '\0', 64);
	scanf("%s", comando);
	while (strcmp(comando, "exit"))
	{
		pid = fork();
		if (pid == 0)
		{
			printf("f\n");
			execlp(comando, comando, NULL); 
			printf("comando no valido\n");
			exit(0);
		}
		else
		{
			if (pid > 0)
			{
				waitpid(pid, &status, 0);
				printf("minishell:");
				memset(comando, '\0', 64);
				scanf("%s", comando);
			}
			else
				perror("Error Fork\n");
		}
	}
	exit(0);
}