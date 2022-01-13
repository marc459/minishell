/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:39:25 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/13 17:12:56 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#if defined(__APPLE__)
# define SO "MACOS"

char	*read_line(char *prompt)
{
	char	*command;

	command = readline(prompt);
	if (command && *command)
		add_history (command);
	return (command);
}
#else
# define SO "LINUX"

char	*read_line(char *prompt)
{
	int		i;
	char	*command;

	i = 0;
	command = ft_calloc(sizeof(char), 64);
	ft_putstr_fd(prompt, 1);
	read(0, command, 64);
	while (command[i])
	{
		if (command[i] == 10)
		{
			command[i] = '\0';
		}
		i++;
	}
	return (command);
}
#endif

void	ft_putbidstr(char **str)
{
	int	x;

	x = 0;
	while (x < ft_bidstrlen(str))
	{
		ft_printf_fd(1, "%s\n", str[x]);
		x++;
	}
}

void	closefds(t_general *g_mini, int i)
{
	if (i > 0 && g_mini->npipes > 0)
		close(g_mini->exec[i - 1].pipe[READ_END]);
	if (i < (int)g_mini->npipes)
		close(g_mini->exec[i].pipe[WRITE_END]);
	if (g_mini->fdout > 1)
		close(g_mini->fdout);
	if (g_mini->fdin > 1)
		close(g_mini->fdin);
	if (g_mini->heredockcontent)
		free(g_mini->heredockcontent);
}
