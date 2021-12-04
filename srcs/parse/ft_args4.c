/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:01:26 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/03 17:56:21 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_addvars(size_t *last, size_t *j)
{
	*last += 1;
	*j += 1;
}

char	*ft_getenv(char *str, size_t *last, size_t *j, t_general *g)
{
	size_t	i;
	char	*aux;
	char	*ret;

	i = -1;
	aux = NULL;
	str++;
	ft_addvars(last, j);
	if (str[i + 1] == '?')
	{
		ft_addvars(last, j);
		return (ft_itoa(g->piperet));
	}
	while (ft_isalpha(str[++i]))
		ft_addvars(last, j);
	if (!i)
		return (ft_strdup("$"));
	else
		aux = ft_substr(str, 0, i);
	ret = ft_strdup(getenv(aux));
	free (aux);
	return (ret);
}

void	ft_joinenv(char **str, t_general *g)
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
			aux = ft_getenv(&str[0][j], &last, &j, g);
			ft_strownjoin(&line, aux);
			free (aux);
		}
	}
	aux = ft_substr(str[0], last, j);
	ft_strownjoin(&line, aux);
	free (aux);
	free(str[0]);
	str[0] = line;
}

void	ft_expvar(t_general *g)
{
	size_t	i;
	char	*aux;

	i = -1;
	while (++i < g->argssize)
	{
		aux = g->args[i].content;
		if (ft_findchar(aux, '$'))
			if ((ft_getposition(aux, '\"') < ft_getposition(aux, '\''))
				|| (ft_getposition(aux, '\"') == ft_getposition(aux, '\'')))
				ft_joinenv(&g->args[i].content, g);
	}
}
