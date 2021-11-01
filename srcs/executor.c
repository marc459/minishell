/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:11:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/01 14:54:26 by marcos           ###   ########.fr       */
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
	int		end[2];

	i = 0;
	//comprobar la existencia de PATHS
	paths = ft_findpath(envp);
	if (!paths)
	{
		ft_printf("PATH not found.\n");
		exit (EXIT_FAILURE);
	}
	
	while(i < g_minishell->npipes)
	{
		pid[0] = fork();
		pipe(end);
		if (pid[0] < 0)
			ft_printf("Error\n");
		if(pid[0] == 0)
		{
			printf("ok\n");
			ft_child(STDIN_FILENO, &g_minishell->args[i].content,envp, end);
		}
		else
			ft_parent(STDOUT_FILENO, &g_minishell->args[i + 2].content, envp, end);
		
		i++;
	}
	
}
