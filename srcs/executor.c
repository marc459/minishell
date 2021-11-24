/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/24 17:58:00 by marcos           ###   ########.fr       */
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
	int	i;
	int	x;

	i = 0;
	x = 0;
	g_mini->fdout = dup(STDOUT_FILENO);
	g_mini->fdin = dup(STDIN_FILENO);
	g_mini->ncommands = g_mini->nexecutables + g_mini->npipes + (g_mini->nredirections * 2) + g_mini->nsemicolons;
	while (i < (g_mini->ncommands))
	{
		if (g_mini->args[i].type == 3)
		{
			g_mini->exec[x].posexec = i;
			x++;
		}
		else if (g_mini->args[i].type == 1)
			g_mini->fdin = open(g_mini->args[i + 1].content, O_RDONLY);
		else if (g_mini->args[i].type == 2)
			g_mini->fdout = open(g_mini->args[i + 1].content,
					O_CREAT | O_RDWR | O_TRUNC, 0755);
		i++;
	}
}

void	administratepipe(int i, t_general *g_mini)
{
	if (i == 1)
		close(g_mini->exec[i - 1].pipe[WRITE_END]);
	if (i > 1)
	{
		close(g_mini->exec[i - 2].pipe[READ_END]);
		close(g_mini->exec[i - 1].pipe[WRITE_END]);
	}
	if (i < g_mini->npipes)
		pipe(g_mini->exec[i].pipe);
}

void	waitforthem(int *childpid, int nchilds)
{
	int	i;

	i = 0;
	while (i < nchilds)
	{
		wait(childpid);
		i++;
	}
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
		administratepipe(i, g_mini);
		pid[0] = fork();
		if (pid[0] == 0)
		{
			cmd = ft_split(g_mini->args[g_mini->exec[i].posexec].content, ' ');
			administratestds(i, g_mini);
			if(!ft_strncmp(cmd[0], "pwd", 3) || !ft_strncmp(cmd[0], "export", 6) 
			|| !ft_strncmp(cmd[0], "unset", 4) || !ft_strncmp(cmd[0], "cd", 2)
			|| !ft_strncmp(cmd[0], "env", 3)
			|| (!ft_strncmp(cmd[0], "echo", 4) && !ft_strncmp(cmd[1], "-n", 2)))
			{
				//printf("Builtin detected\n");
				ft_parsebuiltin(g_mini, cmd);
			}
			else
			{
				ft_child(cmd, envp, &g_mini->fdout);
			}
			ft_freebidstr(cmd);
			exit (EXIT_FAILURE);
		}
		else if (pid[0] < 0)
			printf("Error");
	
		
		i++;
	}
	waitforthem(&i, g_mini->nexecutables);
	free(g_mini->exec);
}
