/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:52:40 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/08 16:35:43 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	while (++i < len)
		res[i] = f (i, s[i]);
	res[i] = '\0';
	return (res);
}
