/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2022/01/08 19:10:30 by marcos           ###   ########.fr       */
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
		{
			g_mini->fdin = STDIN_FILENO;
			//printf("1 fdin %d\n",g_mini->fdin);
		}
			
		if (g_mini->npipes > 0 && g_mini->fdout == -2)
			g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
		else if (g_mini->fdout == -2)
		{
			g_mini->fdout = STDOUT_FILENO;
			//printf("1 fdout %d\n",g_mini->fdout);
		}
		close(g_mini->exec[i].pipe[READ_END]);
	}
	else if (i == (int)(g_mini->nexecutables - 1))
	{
		for(int x = 0; x < g_mini->npipes;x++)
		{
			printf("pipe[%d] [%d,%d]\n", x, g_mini->exec[x].pipe[0],g_mini->exec[x].pipe[1]);
		}
		if (g_mini->fdout == -2)
		{
			g_mini->fdout = STDOUT_FILENO;
			printf("3 fdout %d\n",g_mini->fdout);
			
		}
			
		if (g_mini->fdin == -2)
			g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
		//printf("3 fdin %d\n",g_mini->fdin);
		//printf("3 pipe2[1] %d\n",g_mini->exec[i - 1].pipe[READ_END]);
	}
	else
	{
		if (g_mini->fdin == -2)
			g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
		if (g_mini->fdout == -2)
			g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
		//printf("2 fdin %d\n",g_mini->fdin);
		//printf("2 fdout %d\n",g_mini->fdout);
		close(g_mini->exec[i].pipe[READ_END]);
	}
}

void	administratepipe(int i, t_general *g_mini)
{
	if (g_mini->npipes > 0)
	{
		if (i == (int)(g_mini->nexecutables - 1))
		{
		//	printf("asfdasf1\n");
			//close(g_mini->exec[i - 1].pipe[WRITE_END]);
			if (i > 1)
				close(g_mini->exec[i - 2].pipe[READ_END]);
		}
		else if (i > 0)
		{
			//printf("asfdasf2\n");
			//close(g_mini->exec[i - 1].pipe[WRITE_END]);
		}
			
	}
	if (i < (int)g_mini->npipes)
	{
		pipe(g_mini->exec[i].pipe);
		//printf("creatingpipe %d %d\n",g_mini->exec[i].pipe[0],g_mini->exec[i].pipe[1]);
	}
}
