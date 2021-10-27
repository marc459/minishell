/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:07:10 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/28 00:40:24 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_iniparse(t_parse *parse)
{
	parse->comand = -1;
	parse->quot = 1;
	parse->dquot = 1;
	parse->comndssize = 0;
}

void	ft_pcont(t_parse *parse, size_t type)
{
	if (type)
	{
		parse->comndssize++;
		parse->comand = 1;
	}
	else
	{
		parse->comndssize++;
		parse->comand = 0;
	}
}

size_t	ft_comndssize(char *str)
{
	t_parse	p;
	size_t	i;

	i = -1;
	ft_iniparse(&p);
	while (++i < ft_strlen(str))
	{
		if (str[i] == '\'' && p.dquot > 0)
			p.quot = -p.quot;
		else if (str[i] == '\"' && p.quot > 0)
			p.dquot = -p.dquot;
		else if (ft_spchar(str[i]) && p.quot > 0 && p.dquot > 0)
			ft_pcont(&p, 1);
		else if (p.comand)
			ft_pcont(&p, 0);
	}
	return (p.comndssize);
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

char	*ft_substrsp(char *str, size_t *i)
{
	size_t	len;
	size_t	it;

	len = 1;
	it = *i;
	if (*i < (ft_strlen(str) - 1))
	{
		if ((str[*i] == '>' && str[*i + 1] == '>')
			|| (str[*i] == '<' && str[*i + 1] == '<'))
		{
			len++;
			*i += 1;
		}
	}
	return (ft_substr(str, it, len));
}

char	**ft_fillcomands(size_t size, char *str)
{
	t_parse	p;
	size_t	ini;
	size_t	i;
	size_t	j;
	char	**comnds;

	ini = 0;
	i = -1;
	j = 0;
	ft_iniparse(&p);
	comnds = malloc(sizeof(char *) * size);
	if (!comnds)
		return (NULL);
	while (++i < ft_strlen(str))
	{
		if (str[i] == '\'' && p.dquot > 0)
			p.quot = -p.quot;
		else if (str[i] == '\"' && p.quot > 0)
			p.dquot = -p.dquot;
		else if (ft_spchar(str[i]) && p.quot > 0 && p.dquot > 0)
		{
			if (i - ini > 0)
				comnds[j++] = ft_substr(str, ini, i - ini);
			comnds[j++] = ft_substr(str, i, 1);
			ini = i + 1;
		}
	}
	if (j < size)
		comnds[j++] = ft_substr(str, ini, i - ini);
	return (comnds);
}

void	ft_parse(char *str, t_general *general)
{
	size_t	comndssize;
	char	**comands;
	size_t	i;

	i = -1;
	ft_printgeneral(general);
	comndssize = ft_comndssize(str);
	printf("%zu\n", comndssize);
	printf("\n");
	comands = ft_fillcomands(comndssize, str);
	while (++i < comndssize)
		printf("comnds[%zu] : %s\n", i, comands[i]);
	i = -1;
	while (++i < comndssize)
		free(comands[i]);
	free(comands);
}
