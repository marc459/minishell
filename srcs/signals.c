/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:12:07 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/08 23:31:33 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quitsignal(int sig)
{
	g_piperet = 1;
	printf("\nMinishell-1.0:");
}

void	signals(void)
{
	signal(SIGINT, &quitsignal);
	signal(3, SIG_IGN);
}
