/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:12:27 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/21 11:02:25 by emgarcia         ###   ########.fr       */
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
	g->args[*j].content = ft_dropkeyvalue(str, 1, 1);
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

void	ft_refactquotes(t_general *g)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < g->argssize)
	{
		j = -1;
		while (g->args[i].content[++j])
		{
			if (ft_findchar(g->args[i].content[j], '\"')
				|| ft_findchar(g->args[i].content[j], '\''))
			{
				str = ft_dropquotes(g, g->args[i].content[j]);
				if (!ft_strncmp(str, "export", 6))
				{
					free(str);
					str = ft_dropexportquotes(g, g->args[i].content[j]);
				}
				free (g->args[i].content[j]);
				g->args[i].content[j] = str;
			}
		}
	}
}
