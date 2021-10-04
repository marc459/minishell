/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:19:14 by msantos-          #+#    #+#             */
/*   Updated: 2019/11/18 19:27:38 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	car;
	int		i;
	int		cont;

	car = (char)c;
	i = 0;
	cont = 0;
	while (s[i] != '\0')
	{
		if (s[i] == car)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0' && s[i] == '\0')
		return ((char *)(s + i));
	return (NULL);
}
