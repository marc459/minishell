/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:50:50 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/10 21:23:54 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	temp;
	int				size;
	unsigned int	nr;

	size = 1;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nr = nb * (-1);
	}
	else
		nr = nb;
	temp = nr / 10;
	while (temp > 0)
	{
		size *= 10;
		temp /= 10;
	}
	temp = nr;
	while (size)
	{
		ft_putchar_fd((char)((temp / size)) + 48, fd);
		temp %= size;
		size /= 10;
	}
}
