/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:12:27 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/30 14:18:55 by emgarcia         ###   ########.fr       */
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
			ft_strownjoin(&tmp, ft_substr(str, ultima, i - ultima));
			ultima = i + 1;
			if (str[i] == '\"')
				g->dquot = -g->dquot;
			else if (str[i] == '\'')
				g->quot = -g->quot;
		}
	}
	if (ultima < i)
		ft_strownjoin(&tmp, ft_substr(str, ultima, i - ultima));
	return (tmp);
}

void	ft_findquotes(t_general *g, size_t i)
{
	char	*str;

	str = ft_dropquotes(g, g->args[i].content);
	free (g->args[i].content);
	g->args[i].content = str;
}

void	ft_refactquotes(t_general *g)
{
	size_t	i;

	i = -1;
	while (++i < g->argssize)
		if (ft_findchar(g->args[i].content, '\"')
			|| ft_findchar(g->args[i].content, '\''))
			ft_findquotes(g, i);
}
