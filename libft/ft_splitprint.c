/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 00:21:25 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/09 00:26:30 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_splitprint(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
	{
		write(1, split[i], ft_strlen(split[i]));
		write(1, "\n", 1);
	}
}
