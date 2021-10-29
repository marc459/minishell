
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


int		main(int argc,char **argv, char **env,char **envp)
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
	read_line(command);

	while (ft_strncmp(command, "exit", ft_strlen(command)))
	{
		pid = fork();
		if (pid == 0)
		{
			//lexer
			parser(command);
			//Parser

			//Executor
			executor(envp);							
			execlp(command, command, NULL); 
			ft_printf("Quineshell: %s: command not found\n",command);
			free(command);
			exit(0);
		}
		else
		{
			if (pid > 0)
			{
				wait(&status);
				//command = readline("Quineshell-1.0:");
				//add_history (command);
				//scanf("%s",command);
				read_line(command);
			}
			else
				ft_printf("Error Fork\n");
		}
	}
	return (0);
}
