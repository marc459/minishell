/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/21 16:20:38 by marcos           ###   ########.fr       */
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

void	define_fds(t_general *g)
{
	int		i;
	int		x;
	int		y;
	int		cmdargs;
	char	**tmp;

	i = 0;
	x = 0;
	y = 0;
	cmdargs = 0;
	g->pospipes[y++] = i;
	while ((i < (g->ncommands)))
	{
		if (g->args[i].type == 3 && cmdargs++ == 0)
			g->exec[x++].posexec = i;
		else if (g->args[i].type == 3)
		{
			tmp = ft_bidstrjoin(g->args[g->exec[x - 1].posexec].content, g->args[i].content);
			ft_freebidstr(g->args[g->exec[x - 1].posexec].content);
			g->args[g->exec[x - 1].posexec].content = tmp;
		}
		
		else if (g->args[i].type == 5)
		{
			g->pospipes[y++] = i + 1;
			cmdargs = 0;
		}
		else if (g->args[i].type == 8)
			heredock(g, i);
			
		i++;
	}
	g->nexecutables = x;
}

void	initializefds(t_general *g_mini)
{
	g_mini->fdout2 = dup(STDOUT_FILENO);
	g_mini->fdout = -1;
	g_mini->fdin = -1;
}
void	define_fds2(t_general *g_mini, int exec)
{
	int		i;

	i = g_mini->pospipes[exec];
	initializefds(g_mini);
	while (g_mini->args[i].type != 5 && i < g_mini->ncommands)
	{
		if (g_mini->args[i].type == 1)
		{
			 close(g_mini->fdin);
			 g_mini->fdin = open(g_mini->args[i + 1].content[0], O_RDONLY);
		}
		else if (g_mini->args[i].type == 2)
		{
			close(g_mini->fdout);
			g_mini->fdout = open(g_mini->args[i + 1].content[0],
					O_CREAT | O_RDWR | O_TRUNC, 0755);
		}
		else if (g_mini->args[i].type == 7)
		{
			close(g_mini->fdout);
			g_mini->fdout = open(g_mini->args[i + 1].content[0],
					O_CREAT | O_RDWR | O_APPEND, 0755);
		}
		else if(g_mini->args[i].type == 8)
		{
			g_mini->fdin = open(".tmphd", O_RDONLY);
			unlink(".tmphd");
		}
		i++;
	}
}

char	**ft_bidstrdup(char **str)
{
	char	**strcpy;
	size_t	x;

	if (!str)
		return (NULL);
	x = -1;
	strcpy = (char **)malloc(sizeof(char *) * ft_bidstrlen(str));
	
	if (str == NULL)
		return (NULL);
	while(++x < ft_bidstrlen(str))
		strcpy[x] = ft_strdup(str[x]);
	return (strcpy);
	
}

char	**ft_bidstrjoin(char **str,char **str2)
{
	char	**strcpy;
	size_t	x;
	size_t	y;
	size_t	z;
	size_t	len;

	if (!str)
		return (NULL);
	x = -1;
	y = -1;
	strcpy = (char **)malloc(sizeof(char *) * (ft_bidstrlen(str) + ft_bidstrlen(str2)));
	if (str == NULL)
		return (NULL);
	while(++x < ft_bidstrlen(str))
		strcpy[x] = ft_strdup(str[x]);
	while(++y < ft_bidstrlen(str))
		strcpy[x++] = ft_strdup(str[y]);
	return (strcpy);
	
}

void	ft_executor(t_general *g_mini, char **envp, int *pid)
{
	int		i;
	char	**cmd;

	i = 0;
	g_mini->exec = ft_calloc(sizeof(t_exec), (g_mini->nexecutables + 1));
	define_fds(g_mini);
	while (i < g_mini->nexecutables)
	{
		define_fds2(g_mini, i);
		administratepipe(i, g_mini);
		cmd = ft_bidstrdup(g_mini->args[g_mini->exec[i].posexec].content);
		if (!ft_strncmp(cmd[0], "cd", 2))
			ft_cd(&envp, cmd[1]);
		else if (cmd[0])
			executecmd(g_mini,cmd,envp,i);
		if (i > 0)
			close(g_mini->exec[i - 1].pipe[READ_END]);
		close(g_mini->fdout2);
		close(g_mini->fdout);
		close(g_mini->fdin);
		ft_freebidstr(cmd);
		i++;
	}
	waitforthem(&i, g_mini->nexecutables);
	free(g_mini->exec);
}
