/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:57:21 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/04 16:34:16 by emgarcia         ###   ########.fr       */
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

	i = 0;
	while (i < (g_minishell->ncommands))
	{
		free(g_minishell->args[i].content);
		i++;
	}
	free(g_minishell->args);
	ft_freebidstr(g_minishell->parse.comnds);
}

void	runcflag(t_general	g_minishell, char **environ, char **argv, int pid)
{
	if (ft_bidstrlen(argv) >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		ft_inigeneral(&g_minishell);
		if (ft_strncmp(argv[2], "exit", 5) && ft_strncmp(argv[2], "", 1))
		{
			ft_parse(&g_minishell, argv[2]);
			ft_executor(&g_minishell, environ, &pid);
			ft_freeall(&g_minishell);
		}
		exit (0);
	}
}
