/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:12:27 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/23 14:17:01 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_contsp(t_general *g, size_t i)
{
	size_t	ncomnds;

	ncomnds = 0;
	while (i < g->parse.comndssize && ft_strlen(g->parse.comnds[i++]) == 1)
		ncomnds++;
	return (ncomnds);
}

void	ft_iniarg(t_general *g, size_t *j, char *str)
{
	g->args[*j].content = str;
	if (ft_strlen(str) == 1)
	{
		if (str[0] == '<')
			g->args[(*j)++].type = 1;
		if (str[0] == '>')
			g->args[(*j)++].type = 2;
		if (str[0] == '|')
			g->args[(*j)++].type = 5;
		if (str[0] == ';')
			g->args[(*j)++].type = 6;
	}
	else if (ft_strlen(str) == 2)
	{
		if (str[0] == '>')
			g->args[(*j)++].type = 7;
		if (str[0] == '<')
			g->args[(*j)++].type = 8;
	}
	else
		g->args[(*j)++].type = 3;
}

void	ft_dropquotes(t_general *g, size_t i)
{
	size_t	j;
	size_t	k;
	char	*aux;
	char	*str;
	char	kquote;

	j = -1;
	k = 0;
	aux = g->args[i].content;
	if (ft_getposition(aux, '\"') < ft_getposition(aux, '\''))
		kquote = '\"';
	else if (ft_getposition(aux, '\"') > ft_getposition(aux, '\''))
		kquote = '\'';
	str = ft_trimchar(aux, kquote);
	aux = str;
	str = ft_revtrimchar(str, kquote);
	free (aux);
	g->args[i].content = str;
}

void	ft_refactquotes(t_general *g)
{
	size_t	i;

	i = -1;
	while (++i < g->argssize)
		if (ft_findchar(g->args[i].content, '\"')
			|| ft_findchar(g->args[i].content, '\''))
			ft_dropquotes(g, i);
}
