
#include <minishell.h>

int		main(int argc,char **argv, char **env)
{
	int status;
	pid_t	pid;
	char	*command;
	

	if(argc > 1)
		return (-1);
	signals();
	command = malloc(sizeof(char) * 64);
	ft_memset(command, '\0', 64);
	command = readline("Quineshell-1.0:");
	while (ft_strncmp(command, "exit", ft_strlen(command)))
	{
		pid = fork();
		if (pid == 0)
		{
			//parser
			parser(command);
			// executor execlp(comandpath, comando, NULL); 
			execlp(command, command, NULL); 
			ft_printf("Quineshell: %s: command not found\n",command);
			free(command);
			exit(0);
		}
		else
		{
			if (pid > 0)
			{
				//waitpid(pid, &status, 0);
				wait(&status);
				ft_memset(command, '\0', 64);
				command = readline("Quineshell-1.0:");
			}
			else
				ft_printf("Error Fork\n");
		}
	}
	exit(0);
}
