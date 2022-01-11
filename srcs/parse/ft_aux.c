/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:32:36 by emgarcia          #+#    #+#             */
/*   Updated: 2022/01/11 18:20:57 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_findspchar(char *str)
{
	if (ft_findchar(str, '|') || ft_findchar(str, '<')
		|| ft_findchar(str, '>') || ft_findchar(str, ';'))
		return (1);
	return (0);
}

size_t	ft_spchar(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

size_t	ft_error(size_t ncomands, size_t i, char **cmds)
{
	size_t	j;

	printf("syntax error near unexpected token `");
	j = ncomands - 3;
	while (++j < ncomands)
		printf("%s", cmds[i + j]);
	printf("\'\n");
	return (0);
}

void	ft_inigeneral(t_general *general)
{
	general->npipes = 0;
	general->nexecutables = 0;
	general->nredirections = 0;
	general->quot = 1;
	general->dquot = 1;
	general->parse.comand = 1;
	general->parse.comnds = NULL;
	general->parse.comndssize = 0;
	general->args = NULL;
	general->argssize = 0;
	general->fdout2 = dup(STDOUT_FILENO);
	general->fdout = -2;
	general->fdin = -2;
	general->pospipes = NULL;
}
