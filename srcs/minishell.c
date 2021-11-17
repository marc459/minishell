/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/11/17 17:01:08 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#if defined(__APPLE__)
# define SO "MACOS"

char	*read_line(char *command)
{
	command = readline("Quineshell-1.0:");
	add_history (command);
	return (command);
}
#else
# define SO "LINUX"

char	*read_line(char *command)
{
	int	i;

	i = 0;
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

void	exit_error(char *command)
{
	char	**freespaces;

	freespaces = ft_split(command, ' ');
	if (freespaces[1] && (!str_isnumber(freespaces[1])
			|| ft_bidstrlen(freespaces) > 2))
		printf("minishell: exit: 00-99: numeric argument required\n");
}

void	ft_prompt(t_general *g_m, char **environ)
{
	pid_t		pid;
	char		*command;

	command = calloc(sizeof(char), 64);
	while (ft_strncmp(command, "exit", 4))
	{
		ft_inigeneral(g_m);
		free(command);
		command = read_line(command);
		if (ft_strncmp(command, "exit", 4) && ft_strncmp(command, "", 1))
		{
			system("clear");
			ft_parse(g_m, command);
			printf("%s< QUINES && MEXIL SHELL >%s\n\n", BCyan, Color_Off);
			ft_executor(g_m, environ, &pid);
			printf("%s< REAL BASH >%s\n\n", BCyan, Color_Off);
			system(command);
			ft_freeall(g_m);
		}
		else
			exit_error(command);
	}
	free(command);
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	int			status;
	t_general	g_minishell;

	runcflag(g_minishell, environ, argv, pid);
	signals();
	ft_prompt(&g_minishell, environ);
	printf("exit\n");
	return (0);
}
