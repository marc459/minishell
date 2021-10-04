/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:58:47 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:18:19 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	if (ft_strchr((char *)src, (int)c) == NULL)
		return (NULL);
	while (*src != '\0')
		src++;
	while (*src != c)
		src--;
	return ((char *)src);
}
