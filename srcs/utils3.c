/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:36:17 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/10 18:20:47 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	changestds(t_general *g)
{
	if(g->fdin != 0)
	{
		dup2(g->fdin, STDIN_FILENO);
		close(g->fdin);
		
	}
	if(g->fdout != 1)
	{
		dup2(g->fdout, STDOUT_FILENO);
		close(g->fdout);
	}
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
	system("echo 'Getting leaks from minishell' > /dev/ttys000 ; leaks minishell | grep -iE '[1-9]+ leak[s]* for' > /dev/ttys000");
}

void	checkopenendfds(t_general *g_mini)
{
	if (g_mini->fdin == -1)
		ft_printf_fd(1, "Permission denied\n");
	if (g_mini->fdout == -1)
		ft_printf_fd(1, "Permission denied\n");
}
