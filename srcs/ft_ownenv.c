/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ownenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:59:22 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/25 16:09:09 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
