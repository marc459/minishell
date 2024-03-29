/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:11:14 by emgarcia          #+#    #+#             */
/*   Updated: 2022/01/13 18:30:19 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_arg	*ft_copycleanargs(t_general *g, size_t newargs)
{
	t_arg	*tmp;
	int		i;

	i = -1;
	tmp = malloc(sizeof(t_arg) * (g->argssize + 1));
	if (!tmp)
		exit(0);
	tmp[g->argssize].type = 0;
	tmp[g->argssize].content = NULL;
	i = -1;
	while (++i < (int)g->argssize)
	{
		tmp[i].type = g->args[i].type;
		tmp[i].content = ft_splitdup(g->args[i].content);
		ft_freedouble(g->args[i].content);
	}
	free(g->args);
	g->argssize = newargs;
	return (tmp);
}

void	ft_freecontent(t_arg *args, size_t argssize)
{
	int	i;

	i = -1;
	while (++i < (int)argssize)
		ft_freedouble(args[i].content);
	free(args);
}

void	ft_freedouble(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	ft_freeall(t_general *g)
{
	ft_freedouble(g->parse.comnds);
	ft_freecontent(g->args, g->argssize);
}

void	ft_countthings(t_general *g)
{
	int	i;

	i = -1;
	while (++i < (int)g->argssize)
	{
		if (g->args[i].type == 1 || g->args[i].type == 2
			|| g->args[i].type == 7 || g->args[i].type == 8)
			g->nredirections++;
		else if (g->args[i].type == 3)
			g->nexecutables++;
		else if (g->args[i].type == 5)
			g->npipes++;
	}
	g->ncommands = g->nexecutables + g->npipes
		+ (g->nredirections * 2);
	g->pospipes = NULL;
	if (g->npipes > 0)
		g->pospipes = malloc(sizeof(int) * (g->npipes + 1));
	if (g->pospipes)
		g->pospipes[0] = 0;
	g->exec = ft_calloc(sizeof(t_exec), (g->nexecutables + 1));
	g->nexecutables = g->npipes + 1;
	i = -1;
	if (++i < g->nexecutables)
		g->exec[i].posexec = -1;
}
