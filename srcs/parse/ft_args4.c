/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:01:26 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/24 03:23:35 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	ft_joinenv(char **str)
{
	char	*aux;
	char	*line;
	size_t	j;
	size_t	last;

	last = 0;
	j = -1;
	while (str[0][++j])
	{
		if (str[0][j] == '$')
		{
			line = ft_substr(str[0], last, j);
			last = j;
			aux = line;
			line = ft_strjoin(line, ft_getenv(&str[0][j], &last, &j));
			free (aux);
		}
	}
	aux = line;
	line = ft_strjoin(line, ft_substr(str[0], last, j));
	free (aux);
	free(str[0]);
	str[0] = line;
}

void	ft_expand(t_general *g, size_t i)
{
	char	*aux2;

	aux2 = g->args[i].content;
	if ((ft_getposition(aux2, '\"') < ft_getposition(aux2, '\''))
		|| (ft_getposition(aux2, '\"') == ft_getposition(aux2, '\'')))
		ft_joinenv(&g->args[i].content);
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
