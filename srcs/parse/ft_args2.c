/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 23:15:08 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/11 13:41:58 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_splitcount(t_general *g, size_t *i, size_t *newargs)
{
	char	**split;
	size_t	j;

	split = ft_split(g->args[++*i].content, ' ');
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

char	*ft_joinstring(t_general *g, size_t *j, char **split)
{
	char	*aux;
	char	*line;
	size_t	k;

	k = -1;
	line = NULL;
	while (split[++k])
	{
		if (!k)
		{
			g->args[*j].type = 4;
			g->args[(*j)++].content = ft_strdup(split[k]);
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
	return (line);
}

void	ft_splitarg(t_general *g, size_t *i, size_t *j, t_arg *tmp)
{
	char	**split;
	char	*line;

	g->args[*j].type = tmp[*i].type;
	g->args[(*j)++].content = ft_strdup(tmp[(*i)++].content);
	split = ft_split(tmp[*i].content, ' ');
	if (!split)
		exit(0);
	line = ft_joinstring(g, j, split);
	g->args[*j].type = 3;
	g->args[(*j)++].content = ft_strdup(line);
	free(line);
	ft_freedouble(split);
}

void	ft_droprefact(t_general *g, size_t newargs)
{
	size_t	i;
	size_t	j;
	t_arg	*tmp;

	tmp = ft_copycleanargs(g);
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
	ft_freecontent(tmp);
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
