
#include <minishell.h>

char *stripwhite (char *string)
{
	register char *s, *t;

	for (s = string; *s == ' '; s++)
	;

	if (*s == 0)
		return (s);

	t = s + strlen (s) - 1;
	while (t > s && *t == ' ')
	t--;
	*++t = '\0';

	return s;
}

int		main(int argc,char **argv, char **env)
{
	int status;
	pid_t	pid;
	char	*command;
	char *s;
	

	if(argc > 1)
		return (-1);
	signals();
	command = malloc(sizeof(char) * 64);
	ft_memset(command, '\0', 64);
	command = readline("Quineshell-1.0:");
	add_history (command);
	while (ft_strncmp(command, "exit", ft_strlen(command)))
	{
		pid = fork();
		if (pid == 0)
		{
			//parser
			parser(command);
			// executor execlp(comandpath, comand&&flags, NULL); 
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
				add_history (command);
			}
			else
				ft_printf("Error Fork\n");
		}
	}
	exit(0);
}
