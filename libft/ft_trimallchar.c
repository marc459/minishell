/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimallchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:05:49 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/29 13:55:43 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_trimallchar(char **str, char c)
{
	size_t	i;
	size_t	j;
	char	*final;

	final = calloc(sizeof(char), ft_strlen(*str) - ft_countchar(*str, c) + 1);
	if (!str[0] || !final)
		return ;
	i = -1;
	j = 0;
	while (str[0][++i])
		if (str[0][i] != c)
			final[j++] = str[0][i];
	free (str[0]);
	str[0] = final;
}
