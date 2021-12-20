/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:32:36 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/20 16:47:16 by emgarcia         ###   ########.fr       */
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

void	ft_printgeneral(t_general *general)
{
	size_t	i;

	printf("------------ general struct --------------\n");
	printf("npipes : %zu\n", general->npipes);
	printf("nexecutables : %zu\n", general->nexecutables);
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
		printf("arg[%zu].content : %s\n", i, general->args[i].content);
	}
	printf("-----------------------------------------\n");
}

size_t	ft_error(size_t ncomands)
{
	if (ncomands > 3)
		printf("syntax error near unexpected token `>>'\n");
	else
		printf("syntax error near unexpected token `>'\n");
	return (0);
}

void	ft_inigeneral(t_general *general)
{
	general->npipes = 0;
	general->nexecutables = 0;
	general->nredirections = 0;
	general->quot = 1;
	general->dquot = 1;
	general->parse.comand = -1;
	general->parse.comnds = NULL;
	general->parse.comndssize = 0;
	general->args = NULL;
	general->argssize = 0;
}
