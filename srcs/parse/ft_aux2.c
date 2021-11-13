/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:11:14 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/11 13:42:07 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	ft_freecontent(t_arg *args, size_t argssize)
{
	size_t	i;

	i = -1;
	while (++i < argssize)
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
	ft_freedouble(g->parse.comnds);
	ft_freecontent(g->args, g->argssize);
}

void	ft_countthings(t_general *g)
{
	size_t	i;

	i = -1;
	while (++i < g->argssize)
	{
		if (g->args[i].type == 1 || g->args[i].type == 2)
			g->nredirections++;
		else if (g->args[i].type == 3)
			g->ncomands++;
		else if (g->args[i].type == 5)
			g->npipes++;
	}
}
