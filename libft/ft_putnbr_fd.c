/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 20:31:10 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/08 18:04:05 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_recursive_write(int n, int fd)
{
	char	num;

	num = (n % 10) + '0';
	if (n / 10 > 0)
		ft_recursive_write(n / 10, fd);
	write(fd, &num, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			write(fd, "2", 1);
			n += 2000000000;
		}
		n *= -1;
	}
	ft_recursive_write(n, fd);
}
