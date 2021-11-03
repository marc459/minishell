/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2021/11/03 23:54:25 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	ft_pruveaccess(char *cmd, char **mycmd, char **envp)
{
	if (!access(cmd, X_OK))
	{
		execlp(cmd,cmd,NULL);
		//execve(cmd, mycmd, envp);
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

void	ft_child(int *fdin,int *fdout, char **mycmd1, char **envp, int *stdo)
{
	//printf("executable\n");
	//ls
	char	*cmd;
	size_t	i;
	char	**paths;
	
		
	paths = ft_parsepaths(envp);
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], mycmd1[0]);
		//ft_putstr_fd("Error Child2\n",*stdo);
		if (cmd)
			ft_pruveaccess(cmd, mycmd1, envp);	
	}
	
	ft_printf("Quineshell: %s: command not found\n",mycmd1[0]);
	ft_putstr_fd("Error Child2\n",*stdo);
	
}
