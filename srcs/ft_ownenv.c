/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ownenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:59:22 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/05 03:14:59 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_printsortenv(char **ownenv)
{
	size_t	i;
	char	**sort;

	if (!ownenv)
		return ;
	sort = ft_strsort(ownenv);
	i = -1;
	while (sort[++i])
		printf("declare -x %s\n", sort[i]);
	ft_freedouble(sort);
}

char	**ft_ownenv(char **environ)
{
	char	**ownenv;
	size_t	i;

	ownenv = calloc(sizeof(char *), (ft_splitlen(environ) + 1));
	if (!ownenv || !environ)
		return (NULL);
	i = -1;
	while (++i < ft_splitlen(environ))
		ownenv[i] = ft_strdup(environ[i]);
	return (ownenv);
}
