/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:51:23 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/24 01:06:33 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	parse_flags(const char *format, t_printf *f)
{
	while (format[f->i])
	{
		if (format[f->i] == '%')
		{
			f->i++;
			initialize_flags(f);
			if (ft_strchr("-0123456789.*", format[f->i]))
			{
				flag_sorting(format, f);
			}
			if (ft_strchr("cspdiuxX%", format[f->i]))
			{
				variable_sorting(format, f);
			}
		}
		else
		{
			ft_putchar(format[f->i]);
			f->len++;
		}
		f->i++;
	}
}

int		ft_printf(const char *format, ...)
{
	t_printf *f;

	f = malloc(sizeof(t_printf));
	f->i = 0;
	f->len = 0;
	va_start(f->ap, format);
	if (ft_strchr(format, '%'))
	{
		parse_flags(format, f);
	}
	else
	{
		ft_putstrcounter(format, f);
		f->len = ft_strlen(format);
	}
	return (f->len);
}
