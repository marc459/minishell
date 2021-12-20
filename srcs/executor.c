/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/20 17:18:38 by emgarcia         ###   ########.fr       */
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
	int		cmdargs;
	char	*tmp;

	i = 0;
	x = 0;
	y = 0;
	cmdargs = 0;
	g_mini->pospipes[y++] = i;
	while ((i < (g_mini->ncommands)))
	{
		if (g_mini->args[i].type == 3 && cmdargs++ == 0)
			g_mini->exec[x++].posexec = i;
		else if (g_mini->args[i].type == 3)
		{
			tmp = ft_strjoin(g_mini->args[g_mini->exec[x - 1].posexec].content, " ");
			free(g_mini->args[g_mini->exec[x - 1].posexec].content);
			g_mini->args[g_mini->exec[x - 1].posexec].content = ft_strjoin(tmp, g_mini->args[i].content);
			free(tmp);
		}
		else if (g_mini->args[i].type == 5)
		{
			g_mini->pospipes[y++] = i + 1;
			cmdargs = 0;
		}
		i++;
	}
	g_mini->nexecutables = x;
}

void	define_fds2(t_general *g_mini, int exec)
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
	g_mini->exec = ft_calloc(sizeof(t_exec), (g_mini->nexecutables + 1));
	define_fds(g_mini);
	while (i < g_mini->nexecutables)
	{
		define_fds2(g_mini, i);
		administratepipe(i, g_mini);
		cmd = ft_split(g_mini->args[g_mini->exec[i].posexec].content, ' ');
		if (!ft_strncmp(cmd[0], "cd", 2))
			ft_cd(&envp, cmd[1]);
		if (!ft_strncmp(cmd[0], "unset", 4)
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
		if (i > 0)
			close(g_mini->exec[i - 1].pipe[READ_END]);
		close(g_mini->fdout2);
		close(g_mini->fdout);
		close(g_mini->fdin);
		i++;
		ft_freebidstr(cmd);
	}
	waitforthem(&i, g_mini->nexecutables);
	free(g_mini->exec);
}
