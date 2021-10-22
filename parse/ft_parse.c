/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:07:10 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/22 15:59:37 by emgarcia         ###   ########.fr       */
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

void	ft_inigeneral(void)
{
	g_general.npipes = 0;
	g_general.ncomands = 0;
	g_general.nredirections = 0;
	g_general.args = NULL;
}

void	ft_printgeneral(void)
{
	size_t	i;

	i = -1;
	printf("npipes : %zu\n", g_general.npipes);
	printf("npipes : %zu\n", g_general.ncomands);
	printf("npipes : %zu\n", g_general.nredirections);
	while (g_general.args && g_general.args[++i].content)
		printf("arg[%zu] : %s\n", i, g_general.arg[i].content);
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
	size_t	comndssize;

	ft_inigeneral();
	ft_printgeneral();
	comndssize = ft_comndssize(argc, argv);
	printf("%zu\n", comndssize);
	//comnds = ft_fillcomands(comndssize, argc, argv);
	return (argv);
}
