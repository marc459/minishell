/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:36:17 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/22 20:50:04 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	changestds(t_general *g)
{
	dup2(g->fdin, STDIN_FILENO);
	close(g->fdin);
	dup2(g->fdout, STDOUT_FILENO);
	close(g->fdout);
}

void	givebackstds(t_general *g)
{
	dup2(g->fdincpy, STDIN_FILENO);
	close(g->fdincpy);
	dup2(g->fdoutcpy, STDOUT_FILENO);
	close(g->fdoutcpy);
}

void	ft_checkleaksreturn(void)
{
	printf("return: %d\n", g_piperet);
	system("leaks minishell | grep -E '[1-200] leaks for' >> leaks.txt ");
}
