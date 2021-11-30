/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:53:31 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/30 13:25:08 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_checkquotes(t_general *g)
{
	char	*last;
	char	*tmp;
	size_t	i;

	last = ft_strdup(g->parse.comnds[g->parse.comndssize - 1]);
	while (g->dquot == -1 || g->quot == -1)
	{
		tmp = readline(">");
		i = -1;
		while (tmp[++i])
		{
			if (tmp[i] == '\'' && g->dquot > 0)
				g->quot = -g->quot;
			else if (tmp[i] == '\"' && g->quot > 0)
				g->dquot = -g->dquot;
		}
		ft_strownjoin(&last, tmp);
		free (tmp);
	}
	free (g->parse.comnds[g->parse.comndssize - 1]);
	g->parse.comnds[g->parse.comndssize - 1] = last;
}
/* void	ft_checkquotes(t_general *g)
{
	char	*last;
	char	*tmp;
	char	*aux;
	size_t	i;
	size_t	ultima;

	last = ft_strdup(g->parse.comnds[g->parse.comndssize - 1]);
	while (g->dquot == -1 || g->quot == -1)
	{
		tmp = readline(">");
		i = -1;
		ultima = 0;
		while (tmp[++i])
		{
			if (tmp[i] == '\'')
			{
				if ((g->quot < 0))
				{
					ft_strownjoin(&last, ft_substr(tmp, ultima, i - ultima));
					ultima = i;
				}
				g->quot = -g->quot;
			}
			else if (tmp[i] == '\"')
			{
				if (g->dquot < 0)
				{
					ft_strownjoin(&last, ft_substr(tmp, ultima, i - ultima));
					ultima = i;
				}
				g->dquot = -g->dquot;
			}
		}
		if (ultima < i)
			ft_strownjoin(&last, ft_substr(tmp, ultima, i - ultima));
	}
	//printf("last : %s\n", last);
	free (g->parse.comnds[g->parse.comndssize - 1]);
	g->parse.comnds[g->parse.comndssize - 1] = last;
} */
