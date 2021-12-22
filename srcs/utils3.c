/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:36:17 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/22 19:46:51 by msantos-         ###   ########.fr       */
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
