/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2021/12/17 14:39:11 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_parsepaths(char **envp)
{
	size_t	i;
	char	*paths;
	char	**spaths;
	char	*aux;

	paths = ft_findpath(envp);
	if (!paths)
		return (NULL);
	spaths = ft_split(paths, ':');
	i = -1;
	while (spaths[++i])
	{
		aux = spaths[i];
		spaths[i] = ft_strjoin(spaths[i], "/");
		free(aux);
	}
	return (spaths);
}

void	administratestds(int i, t_general *g_mini)
{
	if (i == 0)
	{
		if(g_mini->fdin  == -1)
			g_mini->fdin = dup(STDIN_FILENO);
		if (g_mini->npipes > 0 && g_mini->fdout == -1)
			g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
		else if(g_mini->fdout  == -1)
			g_mini->fdout = dup(STDOUT_FILENO);
		close(g_mini->exec[i].pipe[READ_END]);
	}
	else if (i == (g_mini->nexecutables - 1))
	{
		if(g_mini->fdout  == -1)
			g_mini->fdout = STDIN_FILENO;
		if(g_mini->fdin  == -1)
			g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
	}
	else
	{
		if(g_mini->fdin  == -1)
			g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
		if(g_mini->fdout  == -1)
			g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
		close(g_mini->exec[i].pipe[READ_END]);
	}

	ft_printf_fd(1,"fds: %d-%d\n",g_mini->fdin,g_mini->fdout);
	dup2(g_mini->fdin, STDIN_FILENO);
	close(g_mini->fdin);
	dup2(g_mini->fdout, STDOUT_FILENO);
	close(g_mini->fdout);
}

void	ft_child(char **fullcmd, char **envp, int *stdo)
{
	char	*cmd;
	size_t	i;
	char	**paths;

	paths = ft_parsepaths(envp);
	i = 0;
	while (paths && paths[i])
	{
		if (ft_strchr(fullcmd[0], '/'))
			cmd = ft_strdup(fullcmd[0]);
		else
			cmd = ft_strjoin(paths[i], fullcmd[0]);
		if (cmd)
		{
			if (!access(cmd, X_OK))
				g_piperet = execve(cmd, fullcmd, envp);
			free(cmd);
		}
		i++;
	}
	if (paths)
		ft_freebidstr(paths);
	ft_putstr_fd("Minishell: ",*stdo);
	ft_putstr_fd(fullcmd[0],*stdo);
	ft_putstr_fd(" command not found\n",*stdo);
	g_piperet = 127;
}
