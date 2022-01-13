/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:12:07 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/13 12:08:14 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quitsignal(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_printf_fd(1, "\n");
	rl_redisplay();
	sig = sig + 1;
	g_piperet = 130;
}

void	sig_main(void)
{
	signal(SIGINT, quitsignal);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_heredock(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	intchild(int sig)
{
	(void)sig;
	g_piperet = -130;
}
