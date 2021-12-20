/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:42:04 by marcos            #+#    #+#             */
/*   Updated: 2021/12/20 21:51:37 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_parsepaths(char **envp)
{
	size_t	i;
	char	*paths;
	char	**spaths;
	char	*aux;

	paths = ft_findpath(envp);
	if (!paths)
		return (NULL);
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

void	administratestds(int i, t_general *g_mini)
{
	if (i == 0)
	{
		if (g_mini->fdin == -1)
			g_mini->fdin = dup(STDIN_FILENO);
		if (g_mini->npipes > 0 && g_mini->fdout == -1)
			g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
		else if (g_mini->fdout == -1)
			g_mini->fdout = dup(STDOUT_FILENO);
		close(g_mini->exec[i].pipe[READ_END]);
	}
	else if (i == (g_mini->nexecutables - 1))
	{
		if (g_mini->fdout == -1)
			g_mini->fdout = dup(STDIN_FILENO);
		if (g_mini->fdin == -1)
			g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
	}
	else
	{
		if (g_mini->fdin == -1)
			g_mini->fdin = g_mini->exec[i - 1].pipe[READ_END];
		if (g_mini->fdout == -1)
			g_mini->fdout = g_mini->exec[i].pipe[WRITE_END];
		close(g_mini->exec[i].pipe[READ_END]);
	}
	dup2(g_mini->fdin, STDIN_FILENO);
	close(g_mini->fdin);
	dup2(g_mini->fdout, STDOUT_FILENO);
	close(g_mini->fdout);
}

void	administratepipe(int i, t_general *g_mini)
{
	if (g_mini->npipes > 0)
	{
		if (i == (g_mini->nexecutables - 1))
		{
			close(g_mini->exec[i - 1].pipe[WRITE_END]);
			if (i > 1)
				close(g_mini->exec[i - 2].pipe[READ_END]);
		}
		else if (i > 0)
			close(g_mini->exec[i - 1].pipe[WRITE_END]);
	}
	if (i < g_mini->npipes)
	{
		pipe(g_mini->exec[i].pipe);
	}
}

void	ft_child(char **fullcmd, char **envp, int *stdo)
{
	char	*cmd;
	size_t	i;
	char	**paths;

	paths = ft_parsepaths(envp);
	i = 0;
	while (paths && paths[i])
	{
		if (ft_strchr(fullcmd[0], '/'))
			cmd = ft_strdup(fullcmd[0]);
		else
			cmd = ft_strjoin(paths[i], fullcmd[0]);
		if (cmd)
		{
			if (!access(cmd, X_OK))
				g_piperet = execve(cmd, fullcmd, envp);
			free(cmd);
		}
		i++;
	}
	if (paths)
		ft_freebidstr(paths);
	ft_putstr_fd("Minishell: ",*stdo);
	ft_putstr_fd(fullcmd[0],*stdo);
	ft_putstr_fd(" command not found\n",*stdo);
	g_piperet = 127;
}

void	executecmd(t_general *g_mini, char **cmd, char **envp, int i)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		administratestds(i, g_mini);
		if (!ft_strncmp(cmd[0], "unset", 4)
			|| !ft_strncmp(cmd[0], "export", 6))
			ft_parsebuiltin(g_mini, cmd);
		else
			ft_child(cmd, envp, &g_mini->fdout2);
		ft_freebidstr(cmd);
		exit (g_piperet);
	}
	else if (pid < 0)
		printf("Error");
	if (i > 0)
			close(g_mini->exec[i - 1].pipe[READ_END]);
}

void	waitforthem(int *childpid, int nchilds)
{
	int	i;
	int	j;

	i = 0;
	while (i < nchilds)
	{
		waitpid(-1, &j, 0);
		wait(childpid);
		i++;
	}
	g_piperet = j % 255;
}
