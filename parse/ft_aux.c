/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:32:36 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/02 22:10:50 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

void	ft_printgeneral(t_general *general)
{
	size_t	i;

	i = -1;
	printf("------------ general struct --------------\n");
	printf("npipes : %zu\n", general->npipes);
	printf("ncomands : %zu\n", general->ncomands);
	printf("nredirections : %zu\n", general->nredirections);
	printf("quot : %d\n", general->quot);
	printf("dquot : %d\n", general->dquot);
	printf("comndssize : %zu\n", general->parse.comndssize);
	printf("argssize : %zu\n", general->argssize);
	while (general->args && ++i < general->argssize)
	{
		printf("arg[%zu].type : %zu\n", i, general->args[i].type);
		printf("arg[%zu].content : %s\n", i, general->args[i].content);
	}
	printf("-----------------------------------------\n");
}

void	ft_inigeneral(t_general *general)
{
	general->npipes = 0;
	general->ncomands = 0;
	general->nredirections = 0;
	general->quot = 1;
	general->dquot = 1;
	general->parse.comand = -1;
	general->parse.comnds = NULL;
	general->parse.comndssize = 0;
	general->args = NULL;
	general->argssize = 0;
}

void	leak(void)
{
	system("leaks parse");
}
