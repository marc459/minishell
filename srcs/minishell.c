
#include <minishell.h>

int		main(int argc,char **argv, char **env)
{
	int status;
	pid_t	pid;
	char	*comando;

	if(argc > 1)
		return (-1);
	comando = malloc(sizeof(char) * 64);
	ft_memset(comando, '\0', 64);
	comando = readline("Quineshell-1.0:");
	while (ft_strncmp(comando, "exit", ft_strlen(comando)))
	{
		pid = fork();
		if (pid == 0)
		{
			//parser
			parser(comando);
			// executor execlp(comandpath, comando, NULL); 
			execlp(comando, comando, NULL); 
			ft_printf("Quineshell: %s: command not found\n",comando);
			exit(0);
		}
		else
		{
			if (pid > 0)
			{
				//waitpid(pid, &status, 0);
				wait(&status);
				ft_memset(comando, '\0', 64);
				comando = readline("Quineshell-1.0:");
			}
			else
				ft_printf("Error Fork\n");
		}
	}
	exit(0);
}
