/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:07:10 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/03 20:48:08 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_pcont(t_general *g, size_t type)
{
	if (type)
	{
		g->parse.comndssize++;
		g->parse.comand = 1;
	}
	else
	{
		g->parse.comndssize++;
		g->parse.comand = 0;
	}
}

void	ft_comndssize(t_general *g, char *str)
{
	size_t	i;

	i = -1;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '\'' && g->dquot > 0)
			g->quot = -g->quot;
		else if (str[i] == '\"' && g->quot > 0)
			g->dquot = -g->dquot;
		else if (ft_spchar(str[i]) && g->quot > 0 && g->dquot > 0)
			ft_pcont(g, 1);
		else if (g->parse.comand)
			ft_pcont(g, 0);
	}
}

char	*ft_joincomnd(char **split, size_t *i, size_t size)
{
	char	*comnd;
	char	*aux;

	comnd = NULL;
	while (*i < size && !ft_findspchar(split[*i]))
	{
		if (!comnd)
			comnd = ft_strdup(split[*i]);
		else
		{
			aux = comnd;
			comnd = ft_strjoin(comnd, " ");
			free(aux);
			aux = comnd;
			comnd = ft_strjoin(comnd, split[*i]);
			free(aux);
		}
		*i += 1;
	}
	*i -= 1;
	return (comnd);
}

void	ft_fillcomands(t_general *g, char *str)
{
	size_t	ini;
	size_t	i;
	size_t	j;

	ini = 0;
	i = -1;
	j = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '\'' && g->dquot > 0)
			g->quot = -g->quot;
		else if (str[i] == '\"' && g->quot > 0)
			g->dquot = -g->dquot;
		else if (ft_spchar(str[i]) && g->quot > 0 && g->dquot > 0)
		{
			if (i - ini > 0)
				g->parse.comnds[j++] = ft_substr(str, ini, i - ini);
			g->parse.comnds[j++] = ft_substr(str, i, 1);
			ini = i + 1;
		}
	}
	if (j < g->parse.comndssize)
		g->parse.comnds[j++] = ft_substr(str, ini, i - ini);
}

void	ft_parse(t_general *general, char *str)
{
	ft_comndssize(general, str);
	general->parse.comnds = calloc(sizeof(char *),
			(general->parse.comndssize + 1));
	if (general->parse.comnds)
	{
		ft_fillcomands(general, str);
		ft_iniargs(general);
		ft_refacttypes(general);
	}
}
