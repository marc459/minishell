/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2021/11/03 18:30:56 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	ft_pruveaccess(char *cmd, char **mycmd, char **envp)
{
	if (!access(cmd, X_OK))
	{

		printf("res : %d %s\n", execve(cmd, mycmd, envp),mycmd[1]);
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

/*void	ft_child2(int *fd, int pid, char **mycmd2, char **envp, int *end)
{
	//wc
	char	*cmd;
	int		i;
	char	**paths;
	int stdo = dup(STDOUT_FILENO);

	
	close(end[WRITE_END]);
	dup2(end[READ_END], fd[0]);
	close(end[READ_END]);
	//execlp("wc","wc",NULL);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd2[0]);
		if (cmd)
			ft_pruveaccess(cmd, fd[1], mycmd2, envp);
			
	}
	close(fd[0]);
	ft_printf("Quineshell: %s: command not found\n",mycmd2[0]);
	ft_putstr_fd("Error Parent\n",1);
	ft_printf("Llegue\n");
	exit (EXIT_FAILURE);
}

void	ft_child(int *fd, char **mycmd1, char **envp, int *end)
{
	//ls
	char	*cmd;
	size_t	i;
	char	**paths;
	int stdo = dup(STDOUT_FILENO);

	close(end[READ_END]);
	dup2(end[WRITE_END], fd[1]);
	close(end[WRITE_END]);
	//execlp("ls","ls",NULL);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd1[0]);
		if (cmd)
			ft_pruveaccess(cmd, fd[1], mycmd1, envp);
	}
	ft_printf("Quineshell: %s: command not found\n",mycmd1[0]);
	ft_putstr_fd("Error Child\n",stdo);
	exit (EXIT_FAILURE);
}*/

void	ft_child(int *openfd, char **mycmd1, char **envp, int *closefd)
{
	//ls
	char	*cmd;
	size_t	i;
	char	**paths;
	int stdo = dup(STDOUT_FILENO);
	// ls -> close pipe1[0]
	// grep -> close pipe1[1]
	// wc -> close pipe2[1]
	close(closefd[READ_END]);
	//ls STDIN -> STDIN
	//grep pipe1[0] -> STDIN
	//wc pipe2[0] -> STDIN
	dup2(openfd[0], STDIN_FILENO);
	close(openfd[0]);
	//ls pipe1[1] -> STDOUT
	//grep pipe2[1] -> STDOUT
	//wc STDOUT -> STDOUT
	dup2(openfd[1], STDOUT_FILENO);
	close(closefd[WRITE_END]);
	//execlp("ls","ls",NULL);
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd1[0]);
		if (cmd)
			ft_pruveaccess(cmd, mycmd1, envp);
	}
	ft_printf("Quineshell: %s: command not found\n",mycmd1[0]);
	ft_putstr_fd("Error Child\n",stdo);
	exit (EXIT_FAILURE);
}
