/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:07:10 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/25 16:39:41 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	ft_comndssize(int argc, char **split)
{
	size_t	i;
	size_t	comand;
	size_t	comndssize;

	i = -1;
	comand = 1;
	comndssize = 0;
	while (++i < (size_t)argc)
	{
		if (ft_findchar(split[i], '|') || ft_findchar(split[i], '<')
			|| ft_findchar(split[i], '>') || ft_findchar(split[i], ';'))
		{
			comndssize++;
			comand = 1;
		}
		else if (comand)
		{
			comndssize++;
			comand = 0;
		}
	}
	return (comndssize);
}

void	ft_inigeneral(t_general *general)
{
	general->npipes = 0;
	general->ncomands = 0;
	general->nredirections = 0;
	general->args = NULL;
}

void	ft_printgeneral(t_general *general)
{
	size_t	i;

	i = -1;
	printf("npipes : %zu\n", general->npipes);
	printf("ncomands : %zu\n", general->ncomands);
	printf("nredirections : %zu\n", general->nredirections);
	while (general->args && general->args[++i].content)
		printf("arg[%zu] : %s\n", i, general->args[i].content);
}

char	**ft_fillcomands(size_t size, int argc, char **split)
{
	char	**comnds;
	char	*comnd;
	char	*aux;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	comnds = malloc(sizeof(char *) * size);
	if (!comnds)
		return (NULL);
	comnd = NULL;
	while (++i < (size_t)argc)
	{
		if (ft_findchar(split[i], '|') || ft_findchar(split[i], '<')
			|| ft_findchar(split[i], '>') || ft_findchar(split[i], ';'))
		{
			if (comnd && i > 0)
			{
				comnds[j++] = ft_strdup(comnd);
				free(comnd);
				comnd = NULL;
			}
			comnds[j++] = ft_strdup(split[i]);
		}
		else if (comnd)
		{
			aux = comnd;
			comnd = ft_strjoin(comnd, split[i]);
			free(aux);
		}
		else
			comnd = ft_strdup(split[i]);
	}
	comnds[j] = ft_strdup(comnd);
	free(comnd);
	return (comnds);
}

void	ft_parse(int argc, char **split, t_general *general)
{
	size_t	comndssize;
	char	**comands;
	size_t	i;

	i = -1;
	ft_printgeneral(general);
	comndssize = ft_comndssize(argc, split);
	printf("%zu\n", comndssize);
	printf("\n");
	comands = ft_fillcomands(comndssize, argc, split);
	while (++i < comndssize)
		printf("comnds[%zu] : %s\n", i, comands[i]);
	i = -1;
	while (++i < comndssize)
		free(comands[i]);
	free(comands);
}
