/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:05:23 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/31 05:05:06 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	ft_contsp(t_general *g, size_t *i)
{
	size_t	ncomnds;
	size_t	j;

	ncomnds = 0;
	j = *i - 1;
	while (++j < g->parse.comndssize && ft_strlen(g->parse.comnds[j]) == 1)
		ncomnds++;
	return (ncomnds);
}

void	ft_checksp(t_general *g, size_t *i, size_t ncomands, size_t *size)
{
	if (ncomands == 3 && ((g->parse.comnds[*i][0] == ';'
			&& g->parse.comnds[*i + 1][0] == '<'
		&& g->parse.comnds[*i + 2][0] == '<') || (g->parse.comnds[*i][0] == ';'
		&& g->parse.comnds[*i + 1][0] == '>'
		&& g->parse.comnds[*i + 2][0] == '>')))
	{
		*size += 2;
		*i += 2;
	}
	else if (ncomands == 2 && ((g->parse.comnds[*i][0] == ';'
			&& g->parse.comnds[*i + 1][0] == '<')
		|| (g->parse.comnds[*i][0] == ';' && g->parse.comnds[*i + 1][0] == '>')
		|| (g->parse.comnds[*i][0] == '<' && g->parse.comnds[*i + 1][0] == '<')
		|| (g->parse.comnds[*i][0] == '>'
		&& g->parse.comnds[*i + 1][0] == '>')))
		*i += 1;
	else if (ncomands > 1)
		exit(0);
	*size += 1;
}

void	ft_argssize(t_general *g)
{
	size_t	argssize;
	size_t	ncomnds;
	size_t	i;

	i = -1;
	argssize = 0;
	while (++i < g->parse.comndssize)
	{
		if (ft_strlen(g->parse.comnds[i]) > 1)
			argssize++;
		else
		{
			ncomnds = ft_contsp(g, &i);
			ft_checksp(g, &i, ncomnds, &argssize);
		}
	}
	printf("finalsize : %zu\n", argssize);
}

void	ft_iniargs(t_general *g)
{
	size_t	i;

	ft_argssize(g);
	//g->args = malloc(sizeof(t_arg) * g->argssize);
	g->args = malloc(sizeof(t_arg) * g->parse.comndssize);
	if (g->args)
	{
		i = -1;
		while (++i < g->parse.comndssize)
		{
			g->args[i].type = 1;
			g->args[i].content = ft_strdup(g->parse.comnds[i]);
		}
	}
}
