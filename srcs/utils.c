/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:57:21 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/14 16:04:29 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	str_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-' && str[i] != '+')
			return (0);
		else if (str[i] == '-' && !(str[i + 1] >= '0' && str[i + 1] <= '9'))
			return (0);
		else if (str[i] == '+' && !(str[i + 1] >= '0' && str[i + 1] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	leakatexit(void)
{
	system("leaks minishell");
}

void	free_gminishell(t_general *g_minishell)
{
	int	i;

	i = -1;
	while (++i < (int)g_minishell->argssize)
		ft_freebidstr(g_minishell->args[i].content);
	if (g_minishell->args)
		free(g_minishell->args);
	if (g_minishell->parse.comnds)
		ft_freebidstr(g_minishell->parse.comnds);
	if (g_minishell->pospipes)
		free(g_minishell->pospipes);
	if (g_minishell->pids)
		free(g_minishell->pids);
	if (g_minishell->exec)
		free(g_minishell->exec);
}

void	runcflag(t_general	*g_mini, char **environ, char **argv)
{
	char	**commands;
	int		i;

	i = 0;
	if (ft_bidstrlen(argv) >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		commands = ft_split(argv[2], ';');
		while (i < ft_bidstrlen(commands))
		{
			if (ft_strncmp(commands[i], "exit", 4)
				&& ft_strncmp(commands[i], "", 1))
			{
				ft_inigeneral(g_mini);
				ft_parse(g_mini, commands[i]);
				g_mini->pids = malloc(sizeof(int) * g_mini->nexecutables);
				ft_executor(g_mini, environ);
				free_gminishell(g_mini);
			}
			i++;
		}
		ft_freebidstr(commands);
		ft_freebidstr(g_mini->ownenv);
		exit (g_piperet);
	}
}

void	commandoutput(int ret)
{
	int	pid;

	g_piperet = ret;
	pid = fork();
	if (pid == 0)
		exit (ret);
}
