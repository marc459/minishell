/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:32:36 by emgarcia          #+#    #+#             */
/*   Updated: 2022/01/14 12:00:35 by emgarcia         ###   ########.fr       */
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

size_t	ft_error(size_t ncomands, size_t i, char **cmds)
{
	size_t	j;

	printf("syntax error near unexpected token `");
	j = ncomands - 3;
	while (++j < ncomands)
		printf("%s", cmds[i + j]);
	printf("\'\n");
	return (0);
}

void	ft_inigeneral(t_general *general)
{
	general->hderror = 0;
	general->npipes = 0;
	general->nexecutables = 0;
	general->nredirections = 0;
	general->quot = 1;
	general->dquot = 1;
	general->parse.comand = 1;
	general->parse.comnds = NULL;
	general->parse.comndssize = 0;
	general->args = NULL;
	general->argssize = 0;
	general->fdout2 = dup(STDOUT_FILENO);
	general->fdout = STDOUT_FILENO;
	general->fdin = STDIN_FILENO;
	general->pospipes = NULL;
}

size_t	ft_checkjoinsp(char *str, size_t *spaces)
{
	size_t	i;
	size_t	others;

	others = 1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			(*spaces)++;
		else if (!ft_spchar(str[i]))
			others = 1;
		else if (ft_spchar(str[i]) && others)
			others = 0;
		else if (ft_spchar(str[i]) && !others && !ft_spchar(str[i - 1]))
		{
			printf("syntax error near unexpected token `");
			printf("%c'\n", str[i]);
			return (0);
		}
	}
	return (1);
}
