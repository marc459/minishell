/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2021/11/01 22:14:30 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	ft_pruveaccess(char *cmd, int fd, char **mycmd, char **envp)
{
	if (!access(cmd, R_OK))
	{
		//dup2(fd, STDOUT_FILENO);
		//printf("cmd %s");
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

void	ft_child2(int fd2, int pid, char **mycmd2, char **envp, int *end)
{
	//wc
	char	*cmd;
	int		i;
	char	**paths;
	//int stdo = dup(STDOUT_FILENO);

	
	close(end[WRITE_END]);
	dup2(end[READ_END], STDIN_FILENO);
	close(end[READ_END]);
	execlp("wc","wc",NULL);
	/*paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd2[0]);
		if (cmd)
			ft_pruveaccess(cmd, STDIN_FILENO, mycmd2, envp);
	}
	//close(fd2);
	ft_printf("Quineshell: %s: command not found\n",mycmd2[0]);
	ft_putstr_fd("Error Parent\n",stdo);*/
	exit (EXIT_FAILURE);
}
/*void	ft_parent(int fd2, int pid, char **mycmd2, char **envp, int *end)
{
	//wc
	char	*cmd;
	int		i;
	char	**paths;
	int stdo = dup(STDOUT_FILENO);

	waitpid(pid,NULL,0);
	close(end[WRITE_END]);
	dup2(end[READ_END], STDIN_FILENO);
	close(end[READ_END]);
	execlp("wc","wc",NULL);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd2[0]);
		if (cmd)
			ft_pruveaccess(cmd, STDIN_FILENO, mycmd2, envp);
	}
	//close(fd2);
	ft_printf("Quineshell: %s: command not found\n",mycmd2[0]);
	ft_putstr_fd("Error Parent\n",stdo);
	exit (EXIT_FAILURE);
}*/

void	ft_child(int fd1, char **mycmd1, char **envp, int *end)
{
	//ls
	char	*cmd;
	size_t	i;
	char	**paths;
	int stdo = dup(STDOUT_FILENO);

	close(end[READ_END]);
	dup2(end[WRITE_END], STDOUT_FILENO);
	close(end[WRITE_END]);
	//execlp("ls","ls",NULL);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd1[0]);
		if (cmd)
			ft_pruveaccess(cmd, fd1, mycmd1, envp);
	}
	ft_printf("Quineshell: %s: command not found\n",mycmd1[0]);
	ft_putstr_fd("Error Child\n",stdo);
	exit (EXIT_FAILURE);
}
