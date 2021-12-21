/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:43:49 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/21 22:08:34 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_general *g, char **cmd)
{
	size_t	i;
	size_t	backn;

	i = 0;
	backn = 1;
	while (cmd[++i])
	{
		if (i == 1 && !ft_strncmp(cmd[i], "-n", 2))
			backn = 0;
		else if (backn == 1 && ft_strncmp(cmd[i], "-n", 2))
			printf("%s\n", cmd[i]);
		else if (!ft_strncmp(cmd[i], "-n", 2))
			printf("%s", cmd[i]);
	}
}
