/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:12:07 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/10 18:53:50 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quitsignal(int sig)
{
	g_piperet = 1;
	//printf(BEGIN(1, 49, 34)"\nMinishell-1.0:"CLOSE);
	printf("\n");
}

void	signals(void)
{
	signal(SIGINT, &quitsignal);
	signal(3, SIG_IGN);
}
