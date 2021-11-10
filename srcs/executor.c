/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/10 19:33:06 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

char	*ft_findpath(char **envp)
{
	unsigned int i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
		&& envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

void       ft_executor(t_general *g_minishell, char **envp, int *pid)
{
	char *paths;
	int i;
	int x;
	char **cmd;
	int a;
	int stdo;
	int stdi;
	
	stdo = dup(STDOUT_FILENO);
	stdi = dup(STDIN_FILENO);
	i = 0;
	x = 0;
	g_minishell->exec = calloc(sizeof(t_exec), (g_minishell->ncomands + 1));
	while(i < (g_minishell->ncomands + g_minishell->npipes))
	{
		if(g_minishell->args[i].type == 3)
		{
			g_minishell->exec[x].posexec = i;
			x++;
		}
		i++;
	}
	
	paths = ft_findpath(envp);
	if (!paths)
	{
		ft_printf("PATH not found.\n");
		exit (EXIT_FAILURE);
	}
	i = 0;
	x = 0;
	
	while(i < g_minishell->ncomands)
	{
		if(i == 1)
			close(g_minishell->exec[i - 1].pipe[WRITE_END]);
		if(i > 1)
		{
			close(g_minishell->exec[i - 2].pipe[READ_END]);
			close(g_minishell->exec[i - 1].pipe[WRITE_END]);
		}
		if(i < g_minishell->npipes)
		{
			pipe(g_minishell->exec[i].pipe);
		}
		
		pid[0] = fork();
		
		
		if (pid[0] < 0)
			ft_printf("Error\n");
		else if(pid[0] == 0)
		{
			cmd = ft_split(g_minishell->args[g_minishell->exec[i].posexec].content, ' ');
			if(i == 0)
			{
				
				close(g_minishell->exec[i].pipe[READ_END]);
				dup2(g_minishell->exec[i].pipe[WRITE_END],STDOUT_FILENO);
				close(g_minishell->exec[i].pipe[WRITE_END]);
				dup2(stdi, STDIN_FILENO);
			}
			else if(i == (g_minishell->ncomands - 1))
			{
				dup2(g_minishell->exec[i - 1].pipe[READ_END], STDIN_FILENO);
				close(g_minishell->exec[i - 1].pipe[READ_END]);	
			}
			else
			{
				close(g_minishell->exec[i].pipe[READ_END]);
				dup2(g_minishell->exec[i - 1].pipe[READ_END],STDIN_FILENO);
				dup2(g_minishell->exec[i].pipe[WRITE_END],STDOUT_FILENO);
				close(g_minishell->exec[i].pipe[WRITE_END]);
			}
			ft_child(cmd,envp,&stdi, &stdo);
			ft_freebidstr(cmd);
			
			exit (EXIT_FAILURE);
		}
		i++;
	}
	i= 0;
	while(i < g_minishell->ncomands)
	{
		wait(&a);
		i++;
	}
	free(g_minishell->exec);
}
