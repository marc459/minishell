/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:13:08 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/22 13:45:32 by marcos           ###   ########.fr       */
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

void	heredock(t_general *g_mini, int i)
{
	char	*tmp;
	char	*tmp2;
	pid_t	pid;
	int		status;

	pid = fork();
	if(pid == 0)
	{
		sig_heredock();
		g_mini->fdin = dup(STDIN_FILENO);
		g_mini->heredockcontent = ft_strdup("");
		tmp = ft_calloc(sizeof(char), 64);
		ft_printf_fd(1, ">");
		read(0, tmp, 64);
		while (tmp)
		{
			if((!ft_strncmp(tmp, g_mini->args[i + 1].content[0],
					ft_strlen(g_mini->args[i + 1].content[0]))
				&& (tmp[ft_strlen(g_mini->args[i + 1].content[0])] == '\n')))
			{
				free(tmp);
				createtmpfile(g_mini);
				exit(EXIT_SUCCESS);
			}
			tmp2 = ft_strdup(g_mini->heredockcontent);
			free(g_mini->heredockcontent);
			g_mini->heredockcontent = ft_strjoin(tmp2, tmp);
			free(tmp2);
			tmp2 = ft_strchr(tmp, '\n');
			tmp2[0] = '\0';
			free(tmp);
			tmp = ft_calloc(sizeof(char), 64);
			ft_printf_fd(1, ">");
			read(0, tmp, 64);
		}
		ft_putstr_fd(1, "warning: here-doc delimited by end-of-file\n");
		free(tmp);
		createtmpfile(g_mini);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		sig_ignore();
		waitpid(pid, &status, 0);
		/*if (WIFSIGNALED(status) && WTERMSIG(status) + 128 == 130)
		{
			write(STDOUT_FILENO, "\n", 1);
			return (1);
		}*/
		sig_main();
	}
}
