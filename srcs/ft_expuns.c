/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 07:12:59 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/06 18:46:21 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_parsebuiltin(t_general *g, char **cmd)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cmd[0], "export", 7) && ft_bidstrlen(cmd) == 1)
		ft_printsortenv(g->ownenv);
	else if (!ft_strncmp(cmd[0], "export", 6))
		while (cmd[++i])
			ft_checknewenv(g, cmd[i]);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		while (cmd[++i])
			ft_remenv(g, cmd[i]);
}
