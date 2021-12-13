/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dropquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:30:57 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/13 13:51:49 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_strsubjoin(char **tmp, char *str, size_t i, size_t *ultima)
{
	char	*substr;

	substr = ft_substr(str, *ultima, i - *ultima);
	ft_strownjoin(tmp, substr);
	free(substr);
	*ultima = i + 1;
}

char	*ft_dropquotes(t_general *g, char *str)
{
	size_t	ultima;
	size_t	i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	ultima = 0;
	while (str[++i])
	{
		if ((str[i] == '\"' && g->quot > 0) || (str[i] == '\"' && g->dquot < 0)
			|| (str[i] == '\'' && g->dquot > 0)
			|| (str[i] == '\'' && g->quot < 0))
		{
			ft_strsubjoin(&tmp, str, i, &ultima);
			if (str[i] == '\"')
				g->dquot = -g->dquot;
			else if (str[i] == '\'')
				g->quot = -g->quot;
		}
	}
	if (ultima < i)
		ft_strsubjoin(&tmp, str, i, &ultima);
	g->dquot = 1;
	g->quot = 1;
	return (tmp);
}

char	*ft_dropexportquotes(t_general *g, char *str)
{
	char	**split;
	char	*aux;
	char	*ret;

	if (!ft_strncmp(str, "export", 6))
		return (ft_strdup(str));
	split = ft_split(str, ' ');
	if (!split)
		return (NULL);
	aux = ft_dropquotes(g, split[0]);
	free (split[0]);
	split[0] = NULL;
	split[0] = aux;
	ret = ft_splitjoin(split, ' ');
	ft_freedouble(split);
	return (ret);
}
