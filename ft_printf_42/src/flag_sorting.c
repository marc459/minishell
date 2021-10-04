/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_sorting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 20:04:38 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 19:53:13 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	minus_zero_finder(const char *format, t_printf *f, int width)
{
	if (format[f->i] == '0' && format[(f->i) + 1] == '-')
		f->i++;
	if (format[f->i] == '-')
	{
		f->flag_minus = 1;
		f->i++;
	}
	if (format[f->i] == '0')
	{
		f->flag_zero = 1;
		f->i++;
		if (format[f->i] == '*')
		{
			f->width = va_arg(f->ap, int);
			f->i++;
		}
		else
		{
			while (format[f->i] <= '9' && format[f->i] >= '0')
			{
				width = width * 10 + (format[f->i++] - '0');
				f->width = width;
			}
		}
	}
}

void	asterisk_finder(const char *format, t_printf *f, int width)
{
	if (format[f->i] == '*')
	{
		f->width = va_arg(f->ap, int);
		f->flag_width = 1;
		f->i++;
	}
	else
	{
		while (format[f->i] <= '9' && format[f->i] >= '0')
		{
			width = width * 10 + (format[f->i] - '0');
			f->flag_width = 1;
			f->width = width;
			f->i++;
		}
	}
}

void	dot_finder(const char *format, t_printf *f, int precision)
{
	if (format[f->i] == '.')
	{
		f->flag_precision = 1;
		f->i++;
		if (format[f->i] == '*')
		{
			f->precision = va_arg(f->ap, int);
			f->flag_precision = 1;
			f->i++;
		}
		else
		{
			while (format[f->i] <= '9' && format[f->i] >= '0')
			{
				precision = precision * 10 + (format[f->i] - '0');
				f->precision = precision;
				f->i++;
			}
		}
	}
}

void	flag_sorting(const char *format, t_printf *f)
{
	int width;
	int precision;

	width = 0;
	precision = 0;
	minus_zero_finder(format, f, width);
	asterisk_finder(format, f, width);
	dot_finder(format, f, precision);
	while (!(ft_strchr("cspdiuxX%", format[f->i])))
		f->i++;
}
