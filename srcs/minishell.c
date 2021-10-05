
#include <minishell.h>

int		main(void)
{
	printf( "%s\n", readline( "test> " ) );
	/*int status;
	pid_t	pid;
	char	comando[64];
	printf("minishell: ");
	ft_memset(comando, '\0', 64);
	//scanf("%s", comando);
	readline(comando);
	while (strcmp(comando, "exit"))
	{
		pid = fork();
		if (pid == 0)
		{
			printf("comand->%s\n",comando);
			execlp(comando, comando, NULL); 
			ft_printf("comando no valido\n");
			exit(0);
		}
		else
		{
			if (pid > 0)
			{
				waitpid(pid, -1, 0);
				ft_printf("minishell:");
				ft_memset(comando, '\0', 64);
				scanf("%s", comando);
			}
			else
				perror("Error Fork\n");
		}
	}*/
	exit(0);
}
