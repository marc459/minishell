/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/15 22:31:07 by msantos-         ###   ########.fr       */
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

void	ft_executor(t_general *g_mini, char **envp, int *pid)
{
	char	*paths;
	int		i;
	int		x;
	char	**cmd;
	int		a;
	int		stdo;
	int		stdi;
	
	g_mini->fdout = dup(STDOUT_FILENO);
	g_mini->fdin = dup(STDIN_FILENO);
	i = 0;
	x = 0;
	g_mini->exec = calloc(sizeof(t_exec), (g_mini->ncomands + 1));
	while (i < (g_mini->ncomands + g_mini->npipes + g_mini->nredirections))
	{
		if (g_mini->args[i].type == 3)
		{
			g_mini->exec[x].posexec = i;
			x++;
		}
		else if (g_mini->args[i].type == 1)
			g_mini->fdin = open(g_mini->args[i + 1].content, O_RDONLY);
		else if (g_mini->args[i].type == 2)
			g_mini->fdout = open(g_mini->args[i + 1].content, O_CREAT | O_RDWR | O_TRUNC, 0755);
		i++;
	}
	paths = ft_findpath(envp);
	if (!paths)
	{
		printf("PATH not found.\n");
		exit (EXIT_FAILURE);
	}
	i = 0;
	x = 0;
	while (i < g_mini->ncomands)
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
		pid[0] = fork();
		if (pid[0] < 0)
			printf("Error\n");
		else if (pid[0] == 0)
		{
			cmd = ft_split(g_mini->args[g_mini->exec[i].posexec].content, ' ');
			if (i == 0)
			{
				if(g_mini->npipes > 0)
					g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
				close(g_mini->exec[i].pipe[READ_END]);
				dup2(g_mini->fdout, STDOUT_FILENO);
				close(g_mini->exec[i].pipe[WRITE_END]);
				dup2(g_mini->fdin, STDIN_FILENO);
			}
			else if (i == (g_mini->ncomands - 1))
			{
				dup2(g_mini->exec[i - 1].pipe[READ_END], STDIN_FILENO);
				close(g_mini->exec[i - 1].pipe[READ_END]);
				dup2(g_mini->fdout, STDOUT_FILENO);
			}
			else
			{
				close(g_mini->exec[i].pipe[READ_END]);
				dup2(g_mini->exec[i - 1].pipe[READ_END], STDIN_FILENO);
				dup2(g_mini->exec[i].pipe[WRITE_END], STDOUT_FILENO);
				close(g_mini->exec[i].pipe[WRITE_END]);
			}
			ft_child(cmd, envp, &g_mini->fdin, &g_mini->fdout);
			ft_freebidstr(cmd);
			exit (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < g_mini->ncomands)
	{
		wait(&a);
		i++;
	}
	free(g_mini->exec);
}
