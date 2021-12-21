/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:39:25 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/21 18:40:01 by msantos-         ###   ########.fr       */
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