/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2021/11/10 22:14:12 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	ft_pruveaccess(char *cmd, char **mycmd, char **envp)
{
	if (!access(cmd, X_OK))
	{
		execve(cmd, mycmd, envp);
	}
	free(cmd);
}

char	**ft_parsepaths(char **envp)
{
	size_t	i;
	char	*paths;
	char	**spaths;
	char	*aux;

	paths = ft_findpath(envp);
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

void	ft_child(char **mycmd1, char **envp,int *stdi, int *stdo)
{
	//ls
	char	*cmd;
	size_t	i;
	char	**paths;
	
	printf("cmd: %s",mycmd1[0]);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd1[0]);
		if (cmd)
		{
			ft_pruveaccess(cmd, mycmd1, envp);	
		}
	}
	
	printf("Quineshell: %s: command not found\n",mycmd1[0]);
	ft_putstr_fd("Error Child2\n",*stdo);
	
}
