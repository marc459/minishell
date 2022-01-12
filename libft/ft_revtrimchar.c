/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revtrimchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:32:24 by emgarcia          #+#    #+#             */
/*   Updated: 2022/01/12 16:01:37 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_revtrimchar(char **str, char c)
{
	char	*final;
	int		i;
	int		j;
	size_t	trimed;

	final = ft_calloc(sizeof(char), ft_strlen(str[0]));
	if (!str[0] || !final)
		return ;
	i = ft_strlen(str[0]);
	j = ft_strlen(str[0]) - 2;
	trimed = 0;
	while (--i > -1)
	{
		if ((str[0][i] != c) || (str[0][i] == c && trimed))
			final[j--] = str[0][i];
		else if (str[0][i] == c && !trimed)
			trimed = 1;
	}
	free (str[0]);
	str[0] = final;
}
