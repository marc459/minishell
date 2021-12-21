/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:43:14 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/21 22:13:07 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	ft_printf_fd(*stdo, "Minishell: %s command not found\n", fullcmd[0]);
	g_piperet = 127;
}

void	executecmd(t_general *g_mini, char **cmd, char **envp, int i)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		unlink(".tmphd");
		administratestds(i, g_mini);
		dup2(g_mini->fdin, STDIN_FILENO);
		close(g_mini->fdin);
		dup2(g_mini->fdout, STDOUT_FILENO);
		close(g_mini->fdout);
		if (!ft_strncmp(cmd[0], "exit", 4))
			exit_error(cmd, g_mini);
		else if (!ft_strncmp(cmd[0], "echo", 4))
			ft_echo(g_mini, cmd);
		else
			ft_child(cmd, envp, &g_mini->fdout2);
		ft_freebidstr(cmd);
		exit (g_piperet);
	}
	else if (pid < 0)
		printf("Error");
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
