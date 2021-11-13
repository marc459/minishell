/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_without_minus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:52:10 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:10:13 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_without_minus(long int n)
{
	char		*str;
	long int	nb;
	long int	i;

	nb = n;
	i = ft_intlen(nb);
	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (nb == 0)
		return (str);
	if (nb < 0)
		nb = nb * -1;
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = 48 + (nb % 10);
		nb = nb / 10;
		i--;
	}
	str[i] = 48 + (nb % 10);
	return (str);
}
