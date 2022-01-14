/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/14 15:39:44 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_findpath(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	define_fds(t_general *g, int i, int x, int y)
{
	int		cmdargs;

	cmdargs = 0;
	while (++i < (int)(g->argssize))
	{
		openfiles(g, i);
		if (g->args[i].type == 3 && cmdargs == 0)
		{
			cmdargs = 1;
			g->exec[x].posexec = i;
		}
		else if (defineexec(g, i, x))
			;
		else if (g->args[i].type == 5 && g->pospipes)
		{
			g->pospipes[y++] = i + 1;
			cmdargs = 0;
			x++;
		}
		else if (g->args[i].type == 8 && !g->hderror)
			heredock(g, i);
	}
}

void	openfiles(t_general *g, int i)
{
	if (g->args[i].type == 1)
	{	
		g->fdin = open(g->args[i + 1].content[0], O_RDONLY);
	}
	else if (g->args[i].type == 2)
	{
		g->fdout = open(g->args[i + 1].content[0],
				O_CREAT | O_RDWR | O_TRUNC, 0755);
	}
	else if (g->args[i].type == 7)
	{
		g->fdout = open(g->args[i + 1].content[0],
				O_CREAT | O_RDWR | O_APPEND, 0755);
	}
}

void	define_fds2(t_general *g_mini, int exec, int i)
{
	if (g_mini->pospipes)
		i = g_mini->pospipes[exec];
	while (i < (int)g_mini->ncommands && g_mini->args[i].type != 5)
	{
		openfiles(g_mini, i);
		if (g_mini->args[i].type == 8)
		{
			g_mini->fdin = open(".tmphd", O_RDONLY);
		}
		i++;
	}
}

void	ft_executor(t_general *g_mini, char **envp)
{
	int		i;
	char	**cm;

	i = -1;
	define_fds(g_mini, -1, 0, 1);
	if (g_mini->nexecutables == 0)
		checkopenendfds(g_mini);
	while (++i < (int)g_mini->nexecutables)
	{
		administratepipe(i, g_mini);
		if (g_mini->exec[i].posexec != -1 && !g_mini->hderror)
		{
			cm = g_mini->args[g_mini->exec[i].posexec].content;
			if (g_mini->npipes == 0 && (!ft_strncmp(cm[0], "unset\0", 6)
					|| !ft_strncmp(cm[0], "exit\0", 4)
					|| !ft_strncmp(cm[0], "cd\0", 3)
					|| (!ft_strncmp(cm[0], "export\0", 7)
						&& ft_bidstrlen(cm) > 1)))
				ft_parsebuiltin(g_mini, cm, i);
			else if (cm[0])
				executecmd(g_mini, cm, envp, i);
		}
		closefds(g_mini, i);
	}
	waitforthem(g_mini, g_mini->nexecutables);
}
