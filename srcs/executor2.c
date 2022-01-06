/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2022/01/06 13:29:46 by marcos           ###   ########.fr       */
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
		if (g_mini->npipes > 0)
		{
			close(g_mini->fdout);
			g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
			
		}
		close(g_mini->exec[i].pipe[READ_END]);
	}
	else if (i == (int)(g_mini->nexecutables - 1))
	{
		close(g_mini->fdin);
		g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
	}
	else
	{
		g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
		close(g_mini->fdout);
		g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
		printf("ehcho something in %d\n",g_mini->fdout);
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
		{
			close(g_mini->exec[i - 1].pipe[WRITE_END]);
		}
			
	}
	if (i < (int)g_mini->npipes)
	{
		pipe(g_mini->exec[i].pipe);
		printf("Creating pipe %d-%d\n",g_mini->exec[i].pipe[0], g_mini->exec[i].pipe[1]);
	}
}
