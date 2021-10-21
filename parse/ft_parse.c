/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:07:10 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/20 20:07:47 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	ft_comndssize(int argc, char **argv)
{
	size_t	i;
	size_t	comand;
	size_t	comndssize;

	i = -1;
	comand = 1;
	comndssize = 0;
	while (++i < (size_t)argc)
	{
		if (ft_findchar(argv[i], '|') || ft_findchar(argv[i], '<')
			|| ft_findchar(argv[i], '>') || ft_findchar(argv[i], ';'))
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

/* char	**ft_fillcomands(size_t size, int argc, char ** argv)
{
	char	**comnds;
	char	*comnd;
	size_t	i;

	i = -1;
	comnds = malloc(sizeof(char *) * size);
	if	(!comnds)
		return(NULL);
	while (++i < (size_t)argc)
	{
		
	}
} */

char	**ft_parse(int argc, char **argv)
{
	size_t	i;
	size_t	comndssize;
	//char	**comnds;

	i = 0;
	comndssize = ft_comndssize(argc, argv);
	printf("%zu\n", comndssize);
	//comnds = ft_fillcomands(comndssize, argc, argv);
	return (argv);
}
