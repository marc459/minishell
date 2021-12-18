/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:05:23 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/18 12:33:21 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_error(size_t ncomands)
{
	if (ncomands > 3)
		printf("syntax error near unexpected token `>>'\n");
	else
		printf("syntax error near unexpected token `>'\n");
	return (0);
}

size_t	ft_ifcheckesp(t_general *g, size_t *i, size_t ncomands, size_t *size)
{
	if (ncomands == 3 && ((g->parse.comnds[*i][0] == ';'
			&& g->parse.comnds[*i + 1][0] == '<'
		&& g->parse.comnds[*i + 2][0] == '<') || (g->parse.comnds[*i][0] == ';'
		&& g->parse.comnds[*i + 1][0] == '>'
		&& g->parse.comnds[*i + 2][0] == '>')))
	{
		*size += 1;
		*i += 2;
		return (1);
	}
	else if (ncomands == 2 && ((g->parse.comnds[*i][0] == ';'
			&& g->parse.comnds[*i + 1][0] == '<')
		|| (g->parse.comnds[*i][0] == ';'
		&& g->parse.comnds[*i + 1][0] == '>')))
	{
		*size += 1;
		*i += 1;
		return (1);
	}
	return (0);
}

size_t	ft_checksp(t_general *g, size_t *i, size_t ncomands, size_t *size)
{
	if (ncomands == 2 && ((g->parse.comnds[*i][0] == '<'
			&& g->parse.comnds[*i + 1][0] == '<')
		|| (g->parse.comnds[*i][0] == '>'
		&& g->parse.comnds[*i + 1][0] == '>')))
		*i += 1;
	else if (ncomands > 1)
		return (ft_error(ncomands));
	else
		ft_ifcheckesp(g, i, ncomands, size);
	*size += 1;
	return (1);
}

size_t	ft_argssize(t_general *g)
{
	size_t	argssize;
	size_t	ncomnds;
	size_t	i;

	i = -1;
	argssize = 0;
	while (++i < g->parse.comndssize)
	{
		if (ft_strlen(g->parse.comnds[i]) > 1)
			argssize++;
		else if (ft_strlen(g->parse.comnds[i]))
		{
			ncomnds = ft_contsp(g, i);
			if (!ft_checksp(g, &i, ncomnds, &argssize))
				return (0);
		}
	}
	g->argssize = argssize;
	return (1);
}

void	ft_dropspargs(t_general *g, size_t *i, size_t *j, size_t ncomands)
{
	if (ncomands == 3)
	{
		ft_iniarg(g, j, ft_strdup(g->parse.comnds[*i]));
		ft_iniarg(g, j, ft_strjoin(g->parse.comnds[*i + 1],
				g->parse.comnds[*i + 2]));
		*i += 2;
	}
	else if (ncomands == 2 && g->parse.comnds[*i][0] == ';')
	{
		ft_iniarg(g, j, ft_strdup(g->parse.comnds[*i]));
		ft_iniarg(g, j, ft_strdup(g->parse.comnds[*i + 1]));
		*i += 1;
	}
	else if (ncomands == 2)
	{
		ft_iniarg(g, j, ft_strjoin(g->parse.comnds[*i],
				g->parse.comnds[*i + 1]));
		*i += 1;
	}
	else
		ft_iniarg(g, j, ft_strdup(g->parse.comnds[*i]));
}

void	ft_iniargs(t_general *g)
{
	size_t	i;
	size_t	j;
	size_t	ncomnds;

	if (!ft_argssize(g))
		return ;
	g->args = calloc(sizeof(t_arg), (g->argssize + 1));
	if (!g->args)
		return ;
	i = -1;
	j = 0;
	ncomnds = 0;
	while (++i < g->parse.comndssize)
	{
		if (ft_strlen(g->parse.comnds[i]) > 1)
		{
			g->args[j].type = 3;
			g->args[j++].content = ft_strdup(g->parse.comnds[i]);
		}
		else if (ft_strlen(g->parse.comnds[i]))
		{
			ncomnds = ft_contsp(g, i);
			ft_dropspargs(g, &i, &j, ncomnds);
		}
	}
}
