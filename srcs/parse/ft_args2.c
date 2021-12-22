/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 23:15:08 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/22 11:40:42 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_splitcount(t_general *g, size_t *i, size_t *newargs)
{
	size_t	j;
	char	**split;

	split = ft_splitdup(g->args[++(*i)].content);
	j = 0;
	while (split[j])
		j++;
	if (j > 1)
		*newargs += 3;
	else
		*newargs += 2;
	ft_freedouble(split);
}

char	**ft_joinstring(t_general *g, size_t *j, char **split)
{
	char	**line;
	size_t	k;
	size_t	l;

	if (ft_splitlen(split) == 1)
		line = NULL;
	else
		line = ft_calloc(sizeof(char *), ft_splitlen(split));
	k = -1;
	l = 0;
	while (split[++k])
	{
		if (!k)
		{
			if (g->args[*j - 1].type == 8)
				g->args[*j].type = 10;
			else
				g->args[*j].type = 4;
			g->args[(*j)++].content = ft_dropkeyvalue(split[k], 0, 0);
		}
		else
			line[l++] = ft_strdup(split[k]);
	}
	return (line);
}

void	ft_splitarg(t_general *g, size_t *i, size_t *j, t_arg *tmp)
{
	char	**line;

	g->args[*j].type = tmp[*i].type;
	g->args[(*j)++].content = ft_splitdup(tmp[(*i)++].content);
	line = ft_joinstring(g, j, tmp[*i].content);
	if (line)
	{
		g->args[*j].type = 3;
		g->args[(*j)++].content = ft_splitdup(line);
		ft_freedouble(line);
	}
}

void	ft_droprefact(t_general *g, size_t newargs)
{
	size_t	i;
	size_t	j;
	size_t	oldsizeargs;
	t_arg	*tmp;

	oldsizeargs = g->argssize;
	tmp = ft_copycleanargs(g, newargs);
	g->args = calloc(sizeof(t_arg), g->argssize);
	if (!g->args)
		exit(0);
	i = -1;
	j = 0;
	while (tmp[++i].content)
	{
		if ((tmp[i].type == 1 || tmp[i].type == 2
				|| tmp[i].type == 7 || tmp[i].type == 8)
			&& (tmp[i + 1].content))
			ft_splitarg(g, &i, &j, tmp);
		else
		{
			g->args[j].type = tmp[i].type;
			g->args[j++].content = ft_splitdup(tmp[i].content);
		}
	}
	ft_freecontent(tmp, oldsizeargs);
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
				|| g->args[i].type == 7 || g->args[i].type == 8)
			&& (g->args[i + 1].content))
			ft_splitcount(g, &i, &newargs);
		else
			newargs++;
	}
	ft_droprefact(g, newargs);
}
