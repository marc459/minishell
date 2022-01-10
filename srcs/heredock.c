/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:13:08 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/10 13:21:15 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	createtmpfile(t_general *g_mini)
{
	g_mini->fdin = open(".tmphd",
			O_CREAT | O_RDWR | O_TRUNC, 0755);
	ft_putstr_fd(g_mini->heredockcontent, g_mini->fdin);
	close(g_mini->fdin);
}

void	heredock2(t_general *g_mini, int i, char **tmp)
{
	char	*tmp2;

	if ((!ft_strncmp(tmp[0], g_mini->args[i + 1].content[0],
				ft_strlen(g_mini->args[i + 1].content[0]))
			&& (tmp[0][ft_strlen(g_mini->args[i + 1].content[0])] == '\0')))
	{
		free(tmp[0]);
		createtmpfile(g_mini);
		exit(EXIT_SUCCESS);
	}
	tmp2 = ft_strdup(g_mini->heredockcontent);
	free(g_mini->heredockcontent);
	g_mini->heredockcontent = ft_strjoin(tmp2, tmp[0]);
	free(tmp2);
	free(tmp[0]);
	tmp[0] = readline(">");
}

void	heredock(t_general *g_mini, int i)
{
	char	*tmp;
	pid_t	pid;
	int		status;


	pid = fork();
	if (pid == 0)
	{
		sig_heredock();
		g_mini->fdin = dup(STDIN_FILENO);
		g_mini->heredockcontent = ft_strdup("");
		tmp = readline(">");
		while (tmp)
			heredock2(g_mini, i, &tmp);
		ft_putstr_fd("warning: here-doc delimited by end-of-file\n", 1);
		free(tmp);
		createtmpfile(g_mini);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		sig_ignore();
		waitpid(pid, &status, 0);
		sig_main();
	}
}
