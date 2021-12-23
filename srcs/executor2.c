/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2021/12/23 11:17:01 by emgarcia         ###   ########.fr       */
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
		if (g_mini->fdin == -2)
			g_mini->fdin = dup(STDIN_FILENO);
		if (g_mini->npipes > 0 && g_mini->fdout == -2)
			g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
		else if (g_mini->fdout == -2)
			g_mini->fdout = dup(STDOUT_FILENO);
		close(g_mini->exec[i].pipe[READ_END]);
	}
	else if (i == (int)(g_mini->nexecutables - 1))
	{
		if (g_mini->fdout == -2)
			g_mini->fdout = dup(STDIN_FILENO);
		if (g_mini->fdin == -2)
			g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
	}
	else
	{
		if (g_mini->fdin == -2)
			g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
		if (g_mini->fdout == -2)
			g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
		close(g_mini->exec[i].pipe[READ_END]);
	}
}

void	administratepipe(int i, t_general *g_mini)
{
	if (g_mini->npipes > 0)
	{
		if (i == (int)(g_mini->nexecutables - 1))
		{
			close(g_mini->exec[i - 1].pipe[WRITE_END]);
			if (i > 1)
				close(g_mini->exec[i - 2].pipe[READ_END]);
		}
		else if (i > 0)
			close(g_mini->exec[i - 1].pipe[WRITE_END]);
	}
	if (i < (int)g_mini->npipes)
	{
		pipe(g_mini->exec[i].pipe);
	}
}
