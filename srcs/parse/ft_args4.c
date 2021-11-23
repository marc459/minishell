/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:01:26 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/23 16:47:58 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_joinenv(char *str)
{
	char	*aux;
	char	*aux2;
	char	*aux3;
	char	*final;

	aux = ft_strdup(str);
	aux += (ft_getposition(str, '$') + 1);
	aux2 = aux;
	if (ft_findchar(aux, '\''))
		aux = ft_revtrimchar(aux, '\'');
	final = ft_substr(str, 0, ft_getposition(str, '$'));
	aux3 = final;
	final = ft_strjoin(final, getenv(aux));
	free (aux3);
	if (ft_findchar(aux2, '\''))
	{
		aux3 = final;
		final = ft_strjoin(final, "\'");
		free (aux3);
	}
	aux2 -= (ft_getposition(str, '$') + 1);
	free (aux2);
	return (final);
}

void	ft_expand(t_general *g, size_t i)
{
	char	**split;
	char	*aux;
	char	*str;
	size_t	j;

	split = ft_split(g->args[i].content, ' ');
	j = -1;
	while (split[++j])
	{
		if (ft_findchar(split[j], '$') && ft_findchar(split[j], '\''))
		{
			aux = split[j];
			split[j] = ft_joinenv(split[j]);
			free (aux);
		}
	}
	free(g->args[i].content);
	g->args[i].content = ft_splitjoin(split, ' ');
	ft_freedouble(split);
}

void	ft_expvar(t_general *g)
{
	size_t	i;

	i = -1;
	while (++i < g->argssize)
	{
		if (ft_findchar(g->args[i].content, '$'))
			ft_expand(g, i);
	}
}
