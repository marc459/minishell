/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:32:36 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/11 13:57:17 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_findspchar(char *str)
{
	if (ft_findchar(str, '|') || ft_findchar(str, '<')
		|| ft_findchar(str, '>') || ft_findchar(str, ';'))
		return (1);
	return (0);
}

size_t	ft_spchar(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

void	ft_printgeneral(t_general *general)
{
	size_t	i;

	printf("------------ general struct --------------\n");
	printf("npipes : %zu\n", general->npipes);
	printf("ncomands : %zu\n", general->ncomands);
	printf("nredirections : %zu\n", general->nredirections);
	printf("quot : %d\n", general->quot);
	printf("dquot : %d\n", general->dquot);
	printf("comndssize : %zu\n", general->parse.comndssize);
	printf("argssize : %zu\n", general->argssize);
	/* i = -1;
	while (general->parse.comnds && ++i < general->parse.comndssize)
		printf("comnds[%zu].type : %s\n", i, general->parse.comnds[i]); */
	i = -1;
	while (general->args && ++i < general->argssize)
	{
		printf("arg[%zu].type : %zu\n", i, general->args[i].type);
		printf("arg[%zu].content : %s\n", i, general->args[i].content);
	}
	printf("-----------------------------------------\n");
}

void	ft_inigeneral(t_general *general)
{
	general->npipes = 0;
	general->ncomands = 0;
	general->nredirections = 0;
	general->quot = 1;
	general->dquot = 1;
	general->parse.comand = -1;
	general->parse.comnds = NULL;
	general->parse.comndssize = 0;
	general->args = NULL;
	general->argssize = 0;
}

void	leak(void)
{
	system("leaks parse");
}


size_t	ft_findchar(char *str, char c)
{
	size_t	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

size_t	ft_countcut(char *str)
{
	size_t	i;
	size_t	before;

	if (!str)
		return (0);
	i = -1;
	before = 1;
	while (str[++i] && before)
	{
		if (str[i] == '\n')
			before--;
	}
	return (i);
}

char	*ft_cutstr(char *str)
{
	char	*cut;
	size_t	sizecut;
	size_t	i;

	cut = malloc(sizeof(char) * (ft_countcut(str) + 1));
	if (!cut)
		return (NULL);
	i = -1;
	while (str[++i])
		if (i < ft_countcut(str))
			cut[i] = str[i];
	cut[ft_countcut(str)] = '\0';
	sizecut = ft_countcut(str);
	i = 0;
	while (str[sizecut + i])
	{
		str[i] = str[sizecut + i];
		i++;
	}
	while (str[i])
		str[i++] = '\0';
	return (cut);
}
