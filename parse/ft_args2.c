/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 23:15:08 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/04 00:02:26 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
			g->args[*j].type = 1;
		if (str[0] == '>')
			g->args[*j].type = 2;
		if (str[0] == '|')
			g->args[*j].type = 5;
		if (str[0] == ';')
			g->args[*j].type = 6;
	}
	else if (ft_strlen(str) == 2)
	{
		if (str[0] == '>')
			g->args[*j].type = 7;
		if (str[0] == '<')
			g->args[*j].type = 8;
	}
	else
		g->args[*j].type = 3;
	*j += 1;
}

void	ft_splitcount(t_general *g, size_t *i, size_t *newargs)
{
	char	**split;
	size_t	j;

	*i += 1;
	split = ft_split(g->args[*i].content, ' ');
	if (!split)
		exit(0);
	j = 0;
	while (split[j])
		j++;
	if (j > 1)
		*newargs += 3;
	else
		*newargs += 2;
	ft_freedouble(split);
}

void	ft_splitarg(t_general *g, size_t *i, size_t *j)
{
	char	**split;
	size_t	j;

	*i += 1;
	split = ft_split(g->args[*i].content, ' ');
	if (!split)
		exit(0);
	j = 0;
	while (split[j])
		j++;
	if (j > 1)
		*newargs += 3;
	else
		*newargs += 2;
	ft_freedouble(split);
}

void	ft_droprefact(t_general *g)
{
	size_t	i;
	size_t	j;
	t_arg	*tmp;

	tmp = g->args;
	g->args = calloc(sizeof(t_arg *), g->argssize + 1);
	if (!g->args)
		exit(0);
	i = -1;
	j = 0;
	while (++i < g->argssize)
	{
		if ((g->args[i].type == 1 || g->args[i].type == 2
				|| g->args[i].type == 7) && (g->args[i + 1].content))
			ft_splitarg(g, &i, &j);
		else
		{
			g->args[i].type = tmp[j].type;
			g->args[i].content = ft_strdup(tmp[j++].content);
		}
	}
	free(tmp);
}

void	ft_refacttypes(t_general *g)
{
	size_t	i;
	size_t	newargs;

	newargs = 0;
	i = -1;
	while (++i < g->argssize)
	{
		if ((g->args[i].type == 1 || g->args[i].type == 2
				|| g->args[i].type == 7) && (g->args[i + 1].content))
			ft_splitcount(g, &i, &newargs);
		else
			newargs++;
	}
	if (newargs != g->argssize)
		return ;
	g->argssize = newargs;
	ft_droprefact(g);
}
