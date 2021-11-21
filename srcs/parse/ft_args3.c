/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:12:27 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/21 16:28:50 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_contsp(t_general *g, size_t i)
{
	size_t	ncomnds;

	ncomnds = 0;
	while (i < g->parse.comndssize && ft_strlen(g->parse.comnds[i++]) == 1)
		ncomnds++;
	return (ncomnds);
}

void	ft_iniarg(t_general *g, size_t *j, char *str)
{
	g->args[*j].content = str;
	if (ft_strlen(str) == 1)
	{
		if (str[0] == '<')
			g->args[(*j)++].type = 1;
		if (str[0] == '>')
			g->args[(*j)++].type = 2;
		if (str[0] == '|')
			g->args[(*j)++].type = 5;
		if (str[0] == ';')
			g->args[(*j)++].type = 6;
	}
	else if (ft_strlen(str) == 2)
	{
		if (str[0] == '>')
			g->args[(*j)++].type = 7;
		if (str[0] == '<')
			g->args[(*j)++].type = 8;
	}
	else
		g->args[(*j)++].type = 3;
}

void	ft_erasequotes(char **strquotes)
{
	char	*str;
	size_t	i;

	i = 0;
	str = calloc(sizeof(char), ft_strlen(*strquotes - 1));
	if (!str)
		exit(0);
	while (strquotes[0][++i] && ft_strlen(*strquotes) > 2
		&& i < ft_strlen(*strquotes) - 1)
		str[i - 1] = strquotes[0][i];
	free(*strquotes);
	*strquotes = ft_strdup(str);
	free(str);
}

void	ft_checkquotes(t_general *g, size_t i)
{
	char	**split;
	size_t	join;
	size_t	j;

	split = ft_split(g->args[i].content, ' ');
	j = -1;
	join = 0;
	while (split[++j])
	{
		if (ft_findchar(split[j], '\"')
			|| ft_findchar(split[j], '\''))
		{
			ft_erasequotes(&split[j]);
			join++;
		}
	}
	if (join)
	{
		free(g->args[i].content);
		g->args[i].content = ft_splitjoin(split, ' ');
	}
}

void	ft_refactquotes(t_general *g)
{
	size_t	i;

	i = -1;
	while (++i < g->argssize)
		if (ft_findchar(g->args[i].content, '\"')
			|| ft_findchar(g->args[i].content, '\''))
			ft_checkquotes(g, i);
}
