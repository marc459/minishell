/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:36:17 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/05 09:20:41 by marcos           ###   ########.fr       */
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

void	checkopenendfds(t_general *g_mini)
{
	if (g_mini->fdin == -1)
		ft_printf_fd(1, "Permission denied\n");
	if (g_mini->fdout == -1)
		ft_printf_fd(1, "Permission denied\n");
}
