/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/12/01 17:42:06 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#if defined(__APPLE__)
# define SO "MACOS"

char	*read_line(char *prompt)
{
	char *command;

	command = ft_calloc(sizeof(char), 64);
	//free(command);
	command = readline(prompt);
	add_history (command);
	return (command);
}
#else
# define SO "LINUX"

char	*read_line(char *prompt)
{
	int	i;
	char *command;

	i = 0;
	command = ft_calloc(sizeof(char), 64);
	ft_putstr_fd(prompt,1);
	//scanf("%s");
	read(0,command,64);
	while (command[i])
	{
		if (command[i] == 10)
		{
			command[i] = '\0';
		}
		i++;
	}
	return (command);
}
#endif

void	hola(void)
{
	system("leaks minishell");
}

void	exit_error(char **command)
{
	char	**freespaces;

	freespaces = ft_split(*command, ' ');
	if (freespaces[1] && !str_isnumber(freespaces[1]))
		printf("minishell: exit: 00-99: numeric argument required\n");
	else if (ft_bidstrlen(freespaces) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		*command = ft_strdup("noexit");
	}
	else if (ft_bidstrlen(freespaces) == 1 && (command[0][4] != '\0' && command[0][4] != ' '))
	{
		printf("minishell: %s: command not found\n",command[0]);
		*command = ft_strdup("noexit");
	}
	ft_freebidstr(freespaces);
}

void	ft_prompt(t_general *g_m, char **environ)
{
	pid_t		pid;
	char		*command;
	char		*buf;
	char		**ownenv;

	ownenv = ft_ownenv(environ);
	command = ft_calloc(sizeof(char), 64);
	while (ft_strncmp(command,"exit",4))
	{
		ft_inigeneral(g_m);
		free(command);
		command = read_line("Minishell1-1.0:");
		if (ft_strncmp(command,"exit",4))
		{
			ft_parse(g_m, command);
			printf("%s< QUINES && MEXIL SHELL >%s\n\n", BCyan, Color_Off);
			ft_executor(g_m, ownenv, &pid);
			//printf("%s< REAL BASH >%s\n\n", BCyan, Color_Off);
			//system(command);
			free_gminishell(g_m);
		}
		else
			exit_error(&command);
	}
	free(command);
	ft_freebidstr(ownenv);
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	t_general	g_minishell;

	runcflag(g_minishell, environ, argv, pid);
	//signals();
	ft_prompt(&g_minishell, environ);
	printf("exit\n");
	return (0);
}
