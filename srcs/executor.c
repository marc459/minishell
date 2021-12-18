/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/18 12:24:47 by marcos           ###   ########.fr       */
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

void	define_fds(t_general *g_mini)
{
	int		i;
	int		x;
	int		y;
	char	*command;

	i = 0;
	x = 0;
	y = 0;
	g_mini->ncommands = g_mini->nexecutables + g_mini->npipes
		+ (g_mini->nredirections * 2) + g_mini->nsemicolons;
	g_mini->pospipes = malloc(sizeof(int) * g_mini->npipes + 1);
	g_mini->pospipes[y++] = i;
	while (i < (g_mini->ncommands))
	{
		if (g_mini->args[i].type == 3)
			g_mini->exec[x++].posexec = i;
		if (g_mini->args[i].type == 5)
			g_mini->pospipes[y++] = i + 1;
		i++;
	}
}

void	define_fds2(t_general *g_mini,int exec)
{
	int		i;
	int		x;
	char	*command;

	i = g_mini->pospipes[exec];
	x = 0;
	g_mini->fdout2 = dup(STDOUT_FILENO);
	g_mini->fdout = -1;
	g_mini->fdin = -1;
	g_mini->doeshd = 0;

	printf("i: %d\n",i);

	while (g_mini->args[i].type != 5 && i < g_mini->ncommands)
	{
		if (g_mini->args[i].type == 1)
		{
			 g_mini->doeshd = 0;
			 close(g_mini->fdin);
			 g_mini->fdin = open(g_mini->args[i + 1].content, O_RDONLY);
		}
		else if (g_mini->args[i].type == 2)
		{
			close(g_mini->fdout);
			g_mini->fdout = open(g_mini->args[i + 1].content,
					O_CREAT | O_RDWR | O_TRUNC, 0755);
		}
		else if (g_mini->args[i].type == 7)
		{
			close(g_mini->fdout);
			g_mini->fdout = open(g_mini->args[i + 1].content,
					O_CREAT | O_RDWR | O_APPEND, 0755);
		}
		else if (g_mini->args[i].type == 8)
			heredock(g_mini, i);
		i++;
	}
}

void	administratepipe(int i, t_general *g_mini)
{
	if(g_mini->npipes > 0)
	{
		if (i == (g_mini->nexecutables - 1))
		{
			close(g_mini->exec[i - 1].pipe[WRITE_END]);
			if(i > 1)
				close(g_mini->exec[i - 2].pipe[READ_END]);
		}
		else if(i > 0)
			close(g_mini->exec[i - 1].pipe[WRITE_END]);
	}
	if (i < g_mini->npipes)
	{
		pipe(g_mini->exec[i].pipe);
	}
}

void	waitforthem(int *childpid, int nchilds)
{
	int	i;
	int	j;

	i = 0;
	while (i < nchilds)
	{
		waitpid(-1, &j, 0);
		wait(childpid);
		i++;
	}
	g_piperet = j % 255;
}

void	ft_executor(t_general *g_mini, char **envp, int *pid)
{
	int		i;
	char	**cmd;

	i = 0;
	g_mini->exec = calloc(sizeof(t_exec), (g_mini->nexecutables + 1));
	define_fds(g_mini);
	while (i < g_mini->nexecutables)
	{
		define_fds2(g_mini,i);
		administratepipe(i, g_mini);
		cmd = ft_split(g_mini->args[g_mini->exec[i].posexec].content, ' ');
		if (g_mini->doeshd)
		{
			//administratestds(i, g_mini);
			ft_putstr_fd(g_mini->heredockcontent, 0);
			ft_putstr_fd("\n", 0);
			i++;
		}
		if (!ft_strncmp(cmd[0], "cd", 2))
			ft_cd(&envp, cmd[1]);
		else if (!ft_strncmp(cmd[0], "unset", 4)
			|| !ft_strncmp(cmd[0], "export", 6))
			ft_parsebuiltin(g_mini, cmd);
		else if (cmd[0])
		{
			pid[0] = fork();
			
			if (pid[0] == 0)
			{
				administratestds(i, g_mini);
				ft_child(cmd, envp, &g_mini->fdout2);
				ft_freebidstr(cmd);
				exit (g_piperet);
			}
			else if (pid[0] < 0)
				printf("Error");
		}
		
		if(i > 1)
			close(g_mini->exec[i - 2].pipe[READ_END]);
		close(g_mini->fdout2);
		close(g_mini->fdout);
		close(g_mini->fdin);
		i++;
		ft_freebidstr(cmd);
	}
	waitforthem(&i, g_mini->nexecutables);
	free(g_mini->exec);
}
