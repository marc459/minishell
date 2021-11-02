/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/02 21:33:50 by msantos-         ###   ########.fr       */
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

void       executor(t_general *g_minishell,char **envp,int *pid)
{
	char *paths;
	int i;
	int x;
	int		end[2];
	char **cmd;
	int	*exec;

	i = 0;
	x = 0;
	exec = 0;
	exec = malloc(sizeof(int) * (g_minishell->ncomands + g_minishell->npipes));
	while(i < (g_minishell->ncomands + g_minishell->npipes))
	{
		if(g_minishell->args[i].type == 3)
		{
			exec[x] = i;
			x++;
		}
		i++;
	}
	i = 0;
	x = 0;
	//comprobar la existencia de PATHS
	paths = ft_findpath(envp);
	if (!paths)
	{
		ft_printf("PATH not found.\n");
		exit (EXIT_FAILURE);
	}
	
	while(i < g_minishell->npipes)
	{
		
		pipe(end);
		pid[0] = fork();
		
		if (pid[0] < 0)
			ft_printf("Error\n");
		if(pid[0] == 0)
		{
			cmd = ft_split(g_minishell->args[exec[x]].content, ' ');
			x++;
			exec++;
			ft_child(STDIN_FILENO, cmd,envp, end);
		}
		else
		{
			waitpid(pid[0],NULL,0);
			close(end[WRITE_END]);
			x++;
			cmd = ft_split(g_minishell->args[exec[x]].content, ' ');
			exec++;
			pid[0] = fork();
			if(pid[0] == 0)
				ft_child2(STDOUT_FILENO, pid[0], cmd, envp, end);
			else
           		close(end[READ_END]);
		}
			
		
		i++;
	}
	
}
