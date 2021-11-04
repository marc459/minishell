/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 23:15:08 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/04 21:58:05 by emgarcia         ###   ########.fr       */
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

void	ft_splitarg(t_general *g, size_t *i, size_t *j, t_arg *tmp)
{
	char	**split;
	char	*line;
	char	*aux;
	size_t	k;

	g->args[*j].type = tmp[*i].type;
	g->args[*j].content = ft_strdup(tmp[*i].content);
	*j += 1;
	*i += 1;
	k = -1;
	split = ft_split(tmp[*i].content, ' ');
	if (!split)
		exit(0);
	line = NULL;
	while (split[++k])
	{
		if (!k)
		{
			g->args[*j].type = 4;
			g->args[*j].content = ft_strdup(split[k]);
			*j += 1;
		}
		else
		{
			aux = line;
			line = ft_strjoin(line, split[k]);
			free(aux);
			aux = line;
			line = ft_strjoin(line, " ");
			free(aux);
		}
	}
	g->args[*j].type = 3;
	g->args[*j].content = ft_strdup(line);
	*j += 1;
	free(line);
	ft_freedouble(split);
}

void	ft_droprefact(t_general *g, size_t newargs)
{
	size_t	i;
	size_t	j;
	t_arg	*tmp;

	tmp = g->args;
	//tmp = ft_copycleanargs(g);
	g->argssize = newargs;
	g->args = calloc(sizeof(t_arg), g->argssize + 1);
	if (!g->args)
		exit(0);
	i = -1;
	j = 0;
	while (tmp[++i].content)
	{
		if ((tmp[i].type == 1 || tmp[i].type == 2 || tmp[i].type == 7)
			&& (tmp[i + 1].content))
			ft_splitarg(g, &i, &j, tmp);
		else
		{
			g->args[j].type = tmp[i].type;
			g->args[j++].content = ft_strdup(tmp[i].content);
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
	if (newargs == g->argssize)
		return ;
	ft_droprefact(g, newargs);
}
