/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:43:49 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/23 11:20:41 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(char **cmd)
{
	size_t	i;
	size_t	backn;

	backn = 1;
	if (cmd[1] && ft_strlen(cmd[1]) > 1 && !ft_strncmp(cmd[1], "-n", 2))
	{
		i = 1;
		backn = 0;
	}
	else
		i = 0;
	while (cmd[++i])
	{
		printf("%s", cmd[i]);
		if (i < ft_splitlen(cmd) - 1)
			printf(" ");
	}
	if (backn == 1)
		printf("\n");
	g_piperet = 0;
}
