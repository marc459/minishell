/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2021/11/01 14:18:08 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	ft_pruveaccess(char *cmd, int fd, char **mycmd, char **envp)
{
	if (!access(cmd, R_OK))
	{
		dup2(fd, STDOUT_FILENO);
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
	printf("paths:%s",paths);
	spaths = ft_split(paths, ':');
	free(paths);
	i = -1;
	while (spaths[++i])
	{
		aux = spaths[i];
		spaths[i] = ft_strjoin(spaths[i], "/");
		free(aux);
	}
	return (spaths);
}

void	ft_parent(int fd2, char **mycmd2, char **envp, int *end)
{
	char	*cmd;
	int		i;
	char	**paths;

	wait(&i);
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd2[0]);
		if (cmd)
			ft_pruveaccess(cmd, fd2, mycmd2, envp);
	}
	close(fd2);
	cmd = ft_strjoin("zsh: command not found: ", mycmd2[0]);
	ft_putstr_fd(cmd, 1);
	free(cmd);
	ft_putstr_fd("\n", 1);
	exit (EXIT_FAILURE);
}

void	ft_child(int fd1, char **mycmd1, char **envp, int *end)
{
	char	*cmd;
	size_t	i;
	char	**paths;

	close(end[0]);
	dup2(fd1, STDIN_FILENO);
	close(fd1);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd1[0]);
		printf("cmd:%s\n",cmd);
		if (cmd)
			ft_pruveaccess(cmd, end[1], mycmd1, envp);
	}
	close(end[1]);
	cmd = ft_strjoin("zsh: command not foundd: ", mycmd1[0]);
	ft_putstr_fd(cmd, 1);
	free(cmd);
	ft_putstr_fd("\n", 1);
	exit (EXIT_FAILURE);
}
