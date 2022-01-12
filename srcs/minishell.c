/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2022/01/12 19:48:59 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	checkleaks(void)
{
	char	*leaks;

	leaks = ft_strjoin("leaks ", ft_itoa(getpid()));
	system(leaks);
	free(leaks);
}

int	exit_error(char **command)
{
	if (ft_bidstrlen(command) > 2)
		printf("minishell: exit: to many arguments\n");
	else if (ft_bidstrlen(command) == 1 && (command[0][4] != '\0'
		&& command[0][4] != ' '))
		printf("minishell: %s: command not found\n", command[0]);
	else if (command[1] && !str_isnumber(command[1]))
	{
		printf("minishell: exit: 00-99: numeric argument required\n");
		exit(g_piperet);
	}	
	else
	{
		ft_printf_fd(1, "exit\n");
		exit(g_piperet);
	}
	return (1);
}

void	ft_prompt(t_general *g_m)
{
	char	*command;

	command = ft_calloc(sizeof(char), 64);
	while (command)
	{		
		free(command);
		command = read_line(BEGIN"Minishell-1.0:"CLOSE);
		if (command && command[0] != '\0')
		{
			ft_inigeneral(g_m);
			ft_parse(g_m, command);
			if (g_m->args)
				ft_executor(g_m, g_m->ownenv);
			free_gminishell(g_m);
		}
	}
	free(command);
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	t_general	g_minishell;

	g_piperet = 0;
	argc = 0;
	g_minishell.ownenv = ft_ownenv(environ);
	runcflag(&g_minishell, environ, argv);
	sig_main();
	ft_prompt(&g_minishell);
	ft_freebidstr(g_minishell.ownenv);
	printf("exit\n");
	return (0);
}
