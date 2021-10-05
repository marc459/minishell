
#include <minishell.h>

int		main(void)
{
	int status;
	pid_t	pid;
	char	*comando;
	comando = malloc(sizeof(char) * 64);
	ft_memset(comando, '\0', 64);
	comando = readline("Minishell:");
	while (ft_strncmp(comando, "exit", ft_strlen(comando)))
	{
		pid = fork();
		if (pid == 0)
		{
			execlp(comando, comando, NULL); 
			ft_printf("comando no valido\n");
			exit(0);
		}
		else
		{
			if (pid > 0)
			{
				waitpid(pid, &status, 0);
				ft_memset(comando, '\0', 64);
				comando = readline("Minishell:");
			}
			else
				perror("Error Fork\n");
		}
	}
	exit(0);
}
