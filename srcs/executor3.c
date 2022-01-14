/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:43:14 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/14 12:23:38 by emgarcia         ###   ########.fr       */
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
	if (ft_strchr(fullcmd[0], '/'))
	{
		cmd = ft_strdup(fullcmd[0]);
		if (!access(cmd, X_OK))
			execve(cmd, fullcmd, envp);
		free(cmd);
	}
	while (paths && paths[i])
	{
		cmd = ft_strjoin(paths[i], fullcmd[0]);
		if (!access(cmd, X_OK))
			execve(cmd, fullcmd, envp);
		free(cmd);
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

	signal(SIGINT, intchild);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		administratestds(i, g_mini);
		define_fds2(g_mini, i, 0);
		checkopenendfds(g_mini);
		if (g_mini->fdin >= 0 && g_mini->fdout >= 0)
		{
			changestds(g_mini);
			if (ft_parsebuiltin(g_mini, cmd, i))
				;
			else
				ft_child(cmd, envp, &g_mini->fdout2);
		}
		exit (g_piperet);
	}
	else if (pid < 0)
		ft_printf_fd(1, "Error\n");
	else
		g_mini->pids[i] = pid;
}

void	waitforthem(t_general *g, int nchilds)
{
	int	i;
	int	j;

	i = 0;
	while (i < nchilds)
	{
		waitpid(g->pids[i], &j, 0);
		i++;
	}
	if (g_piperet == -130)
		g_piperet = 130;
	else
		g_piperet = j % 255;
	sig_main();
}

int	defineexec(t_general *g, int i, int x)
{
	char	**tmp;

	if (g->args[i].type == 3)
	{
		tmp = ft_bidstrjoin(g->args[g->exec[x].posexec].content,
				g->args[i].content);
		ft_freebidstr(g->args[g->exec[x].posexec].content);
		g->args[g->exec[x].posexec].content = tmp;
		return (1);
	}
	return (0);
}
