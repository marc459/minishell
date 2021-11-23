/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:01:26 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/23 23:35:25 by emgarcia         ###   ########.fr       */
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

char	*ft_getenv(char *str, size_t *last, size_t *j)
{
	size_t	i;
	char	*env;
	char	aux2;

	i = 0;
	env = NULL;
	str++;
	*last += 1;
	*j += 1;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
	{
		*last += 1;
		*j += 1;
		i++;
	}
	env = ft_substr(str, 0, i);
	return (ft_strdup(getenv(env)));
}

void	ft_expand(t_general *g, size_t i)
{
	char	*aux;
	char	*str;
	size_t	j;
	size_t	last;

	last = 0;
	if ((ft_getposition(g->args[i].content, '\"') < ft_getposition(g->args[i].content, '\''))
		|| (ft_getposition(g->args[i].content, '\"') == ft_getposition(g->args[i].content, '\'')))
	{
		j = -1;
		while (g->args[i].content[++j])
		{
			if (g->args[i].content[j] == '$')
			{
				str = ft_substr(g->args[i].content, last, j);
				last = j;
				aux = str;
				str = ft_strjoin(str, ft_getenv(&g->args[i].content[j], &last, &j));
				free (aux);
			}
		}
		aux = str;
		str = ft_strjoin(str, ft_substr(g->args[i].content, last, j));
		free (aux);
		free(g->args[i].content);
		g->args[i].content = str;
	}
	printf("content : %s\n", g->args[i].content);
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
