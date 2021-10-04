/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:38:01 by msantos-          #+#    #+#             */
/*   Updated: 2019/11/19 16:50:19 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;
	int		salto;

	i = 0;
	salto = '\n' - 0;
	if (s == NULL)
		return ;
	while (i < ft_strlen(s))
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd(salto, fd);
}
