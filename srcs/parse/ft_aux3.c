/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:53:31 by emgarcia          #+#    #+#             */
/*   Updated: 2022/01/03 13:27:29 by emgarcia         ###   ########.fr       */
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
		tmp = read_line(">");
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

size_t	ft_ignorespace(size_t i, char *str)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

char	*ft_dropspace(char *str)
{
	size_t	spaces;
	size_t	i;
	size_t	j;
	char	*strnsp;

	spaces = 0;
	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			spaces++;
	strnsp = ft_calloc(sizeof(char), (ft_strlen(str) - spaces + 1));
	if (!strnsp)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != ' ')
			strnsp[j++] = str[i];
	return (strnsp);
}

size_t	ft_errorfinalarg(void)
{
	printf("syntax error near unexpected token 'newline'\n");
	return (0);
}
