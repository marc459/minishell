/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:01:54 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:49:23 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	i = ft_strlen(s1) + 1;
	str = (char *)malloc(sizeof(char) * i);
	if (!str)
		return (NULL);
	str = ft_memcpy(str, s1, i);
	return (str);
}
