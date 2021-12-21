/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:13:08 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/21 15:44:40 by marcos           ###   ########.fr       */
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

	g_mini->fdin = dup(STDIN_FILENO);
	g_mini->heredockcontent = ft_strdup("");
	tmp = ft_calloc(sizeof(char), 64);
	ft_printf_fd(1,">");
	read(0, tmp, 64);
	while (ft_strncmp(tmp, g_mini->args[i + 1].content,
			ft_strlen(g_mini->args[i + 1].content)))
	{
		tmp2 = ft_strdup(g_mini->heredockcontent);
		free(g_mini->heredockcontent);
		g_mini->heredockcontent = ft_strjoin(tmp2, tmp);
		free(tmp2);
		tmp2 = ft_strchr(tmp, '\n');
		tmp2[0] = '\0';
		free(tmp);
		tmp = ft_calloc(sizeof(char), 64);
		ft_printf_fd(1,">");
		read(0, tmp, 64);
	}
	free(tmp);
	createtmpfile(g_mini);
			
}
