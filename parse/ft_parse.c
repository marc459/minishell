/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:07:10 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/26 21:56:17 by emgarcia         ###   ########.fr       */
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

size_t	ft_comndssize(char *str)
{
	t_parse	p;
	size_t	i;

	i = -1;
	ft_iniparse(&p);
	while (++i < ft_strlen(str))
	{
		if (str[i] == '\'')
			p.quot = -p.quot;
		else if (str[i] == '\"')
			p.dquot = -p.dquot;
		else if (ft_spchar(str[i]) && p.quot > 0 && p.dquot > 0)
		{
			p.comndssize++;
			p.comand = 1;
		}
		else if (p.comand)
		{
			p.comndssize++;
			p.comand = 0;
		}
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
		if (str[i] == '\'')
			p.quot = -p.quot;
		else if (str[i] == '\"')
			p.dquot = -p.dquot;
		else if (ft_spchar(str[i]) && p.quot > 0 && p.dquot > 0)
		{
			comnds[j++] = ft_substr(str, ini, i - ini);
			ini = i + 1;
			comnds[j++] = ft_substr(str, i, 1);
		}
	}
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
