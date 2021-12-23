/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/23 12:48:34 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_findpath(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H')
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	define_fds(t_general *g, int i, int x, int y)
{
	int		cmdargs;
	char	**tmp;

	cmdargs = 0;
	y++;
	while ((i < (int)(g->ncommands)))
	{
		if (g->args[i].type == 3 && cmdargs++ == 0)
			g->exec[x++].posexec = i;
		else if (g->args[i].type == 3)
		{
			tmp = ft_bidstrjoin(g->args[g->exec[x - 1].posexec].content,
					g->args[i].content);
			ft_freebidstr(g->args[g->exec[x - 1].posexec].content);
			g->args[g->exec[x - 1].posexec].content = tmp;
		}
		else if (g->args[i].type == 5 && (cmdargs-- < 42) && g->pospipes)
			g->pospipes[y++] = i + 1;
		else if (g->args[i].type == 8)
			heredock(g, i);
		i++;
	}
	g->nexecutables = x;
}

void	openfiles(t_general *g, int i)
{
	if (g->args[i].type == 1)
	{
		close(g->fdin);
		g->fdin = open(g->args[i + 1].content[0], O_RDONLY);
		if (g->fdin == -1)
			ft_printf_fd(1, "%s: Permission denied\n",
				g->args[i + 1].content[0]);
	}
	else if (g->args[i].type == 2)
	{
		close(g->fdout);
		g->fdout = open(g->args[i + 1].content[0],
				O_CREAT | O_RDWR | O_TRUNC, 0755);
		if (g->fdout == -1)
			ft_printf_fd(1, "%s: Permission denied\n",
				g->args[i + 1].content[0]);
	}
	else if (g->args[i].type == 7)
	{
		close(g->fdout);
		g->fdout = open(g->args[i + 1].content[0],
				O_CREAT | O_RDWR | O_APPEND, 0755);
	}
}

void	define_fds2(t_general *g_mini, int exec, int i)
{
	g_mini->fdout2 = dup(STDOUT_FILENO);
	g_mini->fdout = -2;
	g_mini->fdin = -2;
	if (g_mini->pospipes)
		i = g_mini->pospipes[exec];
	while (i < (int)g_mini->ncommands && g_mini->args[i].type != 5)
	{
		openfiles(g_mini, i);
		if (g_mini->args[i].type == 8)
			g_mini->fdin = open(".tmphd", O_RDONLY);
		i++;
	}
}

void	ft_executor(t_general *g_mini, char **envp)
{
	int		i;
	char	**cm;

	i = 0;
	g_mini->exec = ft_calloc(sizeof(t_exec), (g_mini->nexecutables + 1));
	define_fds(g_mini, 0, 0, 0);
	while (i < (int)g_mini->nexecutables)
	{
		define_fds2(g_mini, i, 0);
		administratepipe(i, g_mini);
		cm = g_mini->args[g_mini->exec[i].posexec].content;
		if (!ft_strncmp(cm[0], "cd", 2))
			ft_cd(&envp, cm[1]);
		else if (!ft_strncmp(cm[0], "unset\0", 6)
			|| !ft_strncmp(cm[0], "export", 6)
			|| (!ft_strncmp(cm[0], "exit", 4) && g_mini->npipes == 0))
			ft_parsebuiltin(g_mini, cm, i);
		else if (cm[0])
			executecmd(g_mini, cm, envp, i);
		closefds(g_mini, i);
		i++;
	}
	waitforthem(&i, g_mini->nexecutables);
	free(g_mini->exec);
}
