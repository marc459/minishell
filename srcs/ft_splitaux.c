/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitaux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:07:59 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/21 12:25:10 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_splitfindchar(char **split, char c)
{
	size_t	i;

	if (!split)
		return (0);
	i = -1;
	while (split[++i])
	{
		if (ft_findchar(split[i], c))
			return (1);
	}
	return (0);
}
