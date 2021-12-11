/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:01:26 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/11 11:46:51 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_addvars(size_t *last, size_t *j)
{
	*last += 1;
	*j += 1;
}

char	*ft_findenv(char *envvar, t_general *g)
{
	size_t	i;
	size_t	varlen;
	size_t	owenvlen;

	i = -1;
	while (g->ownenv[++i])
	{
		if (ft_strncmp(envvar, g->ownenv[i], ft_strlen(envvar)) == 0
			&& (g->ownenv[i][ft_strlen(envvar)] == '='
			|| !g->ownenv[i][ft_strlen(envvar)]))
		{
			varlen = ft_strlen(envvar);
			owenvlen = ft_strlen(g->ownenv[i]);
			return (ft_substr(g->ownenv[i], varlen + 1, owenvlen - varlen - 1));
		}
	}
	return (NULL);
}

char	*ft_getenv(char *str, size_t *last, size_t *j, t_general *g)
{
	size_t	i;
	char	*aux;
	char	*ret;

	aux = NULL;
	str++;
	ft_addvars(last, j);
	i = -1;
	if (str[i + 1] == '?')
	{
		ft_addvars(last, j);
		return (ft_itoa(g_piperet));
	}
	while (ft_isalpha(str[++i]))
		ft_addvars(last, j);
	if (!i && str[i] != '\"' && str[i] != '\'')
		return (ft_strdup("$"));
	else
		aux = ft_substr(str, 0, i);
	ret = ft_findenv(aux, g);
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
		if (ft_findchar(aux, '$') && g->args[i - 1].type != 8)
			if ((ft_getposition(aux, '\"') < ft_getposition(aux, '\''))
				|| (ft_getposition(aux, '\"') == ft_getposition(aux, '\'')))
				ft_joinenv(&g->args[i].content, g);
	}
}
