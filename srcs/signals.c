/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:12:07 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/22 13:49:15 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quitsignal(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_printf_fd(1, "\n");
	rl_redisplay();
	g_piperet = 130;
	commandoutput(130);
}

void	sig_main()
{
	signal(SIGINT, quitsignal);
	//signal(SIGQUIT, SIG_DFL);
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

void	sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}