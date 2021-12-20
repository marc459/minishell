/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:12:07 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/20 16:57:25 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quitsignal(int sig)
{
	g_piperet = 1;
	printf(BEGIN(1, 49, 34)"\nMinishell-1.0:"CLOSE);
	ft_printf_fd(1, "");
}

void	signals(void)
{
	signal(SIGINT, &quitsignal);
	signal(3, SIG_IGN);
}
