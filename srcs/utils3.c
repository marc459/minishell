/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:36:17 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/17 14:06:31 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	changestds(t_general *g)
{
	if (g->fdin != 0)
	{
		dup2(g->fdin, STDIN_FILENO);
		close(g->fdin);
	}
	if (g->fdout != 1)
	{
		dup2(g->fdout, STDOUT_FILENO);
		close(g->fdout);
	}
}

void	checkopenendfds(t_general *g_mini)
{
	if (g_mini->fdin == -1)
		ft_printf_fd(1, "Permission denied\n");
	if (g_mini->fdout == -1)
		ft_printf_fd(1, "Permission denied\n");
}

void	ft_checkleaksreturn(void)
{
	printf("return: %d\n", g_piperet);
	system("echo 'Getting leaks from minishell' > /dev/ttys000 ; leaks minishell | grep -iE '[1-9]+ leak[s]* for' > /dev/ttys000");
}

void	ft_printgeneral(t_general *general)
{
	size_t	i;
	size_t	j;

	printf("------------ general struct --------------\n");
	printf("npipes : %zu\n", general->npipes);
	printf("nexecutables : %d\n", general->nexecutables);
	printf("nredirections : %zu\n", general->nredirections);
	printf("quot : %d\n", general->quot);
	printf("dquot : %d\n\n", general->dquot);
	printf("comndssize : %zu\n", general->parse.comndssize);
	printf("COMMNDS\n");
	i = -1;
	while (general->parse.comnds && ++i < general->parse.comndssize)
		printf("comnds[%zu] : %s\n", i, general->parse.comnds[i]);
	printf("\n");
	printf("argssize : %zu\n", general->argssize);
	printf("ARGS\n");
	i = -1;
	while (general->args && ++i < general->argssize)
	{
		printf("arg[%zu].type : %zu\n", i, general->args[i].type);
		j = -1;
		while (general->args[i].content[++j])
			printf("arg[%zu].content[%zu] : %s\n", i, j, general->args[i].content[j]);
	}
	printf("-----------------------------------------\n");
}
