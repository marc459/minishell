/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percentage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 23:44:26 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 00:17:34 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	check_zeroflag_0(t_printf *f)
{
	int len;
	int i;

	i = 0;
	if (f->flag_zero == 1 && f->flag_minus == 0)
	{
		len = f->width - 1;
		while (i < len)
		{
			ft_putchar('0');
			f->len++;
			i++;
		}
	}
	else if (f->flag_zero == 1 && f->flag_minus == 1)
	{
		len = f->width - 1;
		while (i < len)
		{
			ft_putchar(' ');
			f->len++;
			i++;
		}
	}
}

void	check_widthflag_0(t_printf *f)
{
	int len;
	int i;

	i = 0;
	if (f->flag_width == 1)
	{
		len = f->width - 1;
		while (i < len)
		{
			ft_putchar(' ');
			f->len++;
			i++;
		}
	}
}

void	print_0(t_printf *f)
{
	if (f->flag_minus == 1 || f->width < 0)
	{
		f->flag_minus = 1;
		if (f->width < 0)
			f->width = f->width * (-1);
		ft_putchar('%');
		f->len++;
		check_widthflag_0(f);
		check_zeroflag_0(f);
	}
	else
	{
		check_zeroflag_0(f);
		check_widthflag_0(f);
		ft_putchar('%');
		f->len++;
	}
}
