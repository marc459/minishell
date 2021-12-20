/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:12:07 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/20 17:44:52 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quitsignal(int sig)
{
	g_piperet = 1;
	printf(BEGIN(1, 49, 34)"\nMinishell-1.0:"CLOSE);
	ft_printf_fd(1, "");
}

void	signals(t_general *g)
{
	signal(SIGINT, &quitsignal);
	signal(3, SIG_IGN);
}
