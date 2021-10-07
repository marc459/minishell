/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:12:07 by msantos-          #+#    #+#             */
/*   Updated: 2021/10/07 22:36:51 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quitsignal(int sig)
{
	ft_printf("\nQuineshell-1.0:");
}
void	signals()
{
	//signal(SIGQUIT, &quitsignal);
	//signal(SIGKILL, &quitsignal);
	signal(SIGINT, &quitsignal); //// 5 - Ctrl + C
	//signal(SIGTRAP, &quitsignal); // 5 - Ctrl + Z
}