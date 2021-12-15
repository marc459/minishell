/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrcounter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 01:01:37 by marcos            #+#    #+#             */
/*   Updated: 2021/12/15 18:21:49 by msantos-         ###   ########.fr       */
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
		ft_putchar_fd(s[i],f->fd);
		f->len++;
		i++;
	}
}