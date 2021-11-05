/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:11:14 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/05 21:38:24 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_arg	*ft_copycleanargs(t_general *g)
{
	t_arg	*tmp;
	size_t	i;

	i = -1;
	tmp = malloc(sizeof(t_arg) * (g->argssize + 1));
	if (!tmp)
		exit(0);
	tmp[g->argssize].type = 0;
	tmp[g->argssize].content = NULL;
	i = -1;
	while (++i < g->argssize)
	{
		tmp[i].type = g->args[i].type;
		tmp[i].content = ft_strdup(g->args[i].content);
		free(g->args[i].content);
	}
	free(g->args);
	return (tmp);
}

void	ft_freecontent(t_arg *args)
{
	size_t	i;

	i = -1;
	printf("Llegue\n");
	while (args[++i].content)
		free(args[i].content);
	free(args);
}

void	ft_freedouble(char **split)
{
	size_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	ft_freeall(t_general *g)
{
	size_t	i;

	/* i = -1;
	while (++i < g->parse.comndssize)
		free(g->parse.comnds[i]);
	free(g->parse.comnds); */
	ft_freedouble(g->parse.comnds);
	i = -1;
	while (++i < g->argssize)
		free(g->args[i].content);
	free(g->args);
}
