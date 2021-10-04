/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrcounter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 01:01:37 by marcos            #+#    #+#             */
/*   Updated: 2021/06/24 01:01:44 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putstrcounter(const char *s, t_printf *f)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return ;
	while (i < ft_strlen(s))
	{
		write(1, &s[i], 1);
		f->len++;
		i++;
	}
}