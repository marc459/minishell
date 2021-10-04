/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:56:22 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/01 20:23:31 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*mini_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void	get_path(char *cmd, char *envp[], char **f_path)
{
	char	**paths;
	char	*path;
	char	*path_cmd;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(ft_strchr(mini_path(envp), '/'), ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(path, cmd);
		free(path);
		fd = open(path_cmd, O_RDONLY);
		if (fd >= 0)
		{
			*f_path = path_cmd;
			free_matrix(paths);
			close(fd);
			return ;
		}
		free(path_cmd);
		i++;
	}
	
	free_matrix(paths);
}

char	**split_cmd_arg(char *argv)
{
	char	**cmd_arg;

	cmd_arg = ft_split(argv, ' ');
	return (cmd_arg);
}
