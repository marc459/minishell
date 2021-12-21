/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:12:07 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/21 18:23:05 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quitsignal(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_printf_fd(1, "\n");
	rl_redisplay();
	g_piperet = 1;
}

void	signals(void)
{
	signal(SIGINT, &quitsignal);
	signal(3, SIG_IGN);
}
