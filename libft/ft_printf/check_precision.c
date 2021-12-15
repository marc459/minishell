/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 20:19:00 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 20:27:45 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	check_precisionflag_i(t_printf *f, int integer)
{
	int len;
	int i;

	i = 0;
	if (f->flag_precision == 1)
	{
		len = f->precision - ft_intlen(integer);
		if (len < 0)
			len = 0;
		if (integer < 0)
		{
			ft_putchar('-');
			f->len++;
		}
		ft_print_charxtimes(f, '0', len);
	}
}

char	*check_precisionflag_s(t_printf *f, const char *str)
{
	char *tmp;

	if (f->flag_precision == 1)
	{
		if ((size_t)f->precision <= ft_strlen(str))
		{
			tmp = ft_substr(str, 0, f->precision);
			str = ft_strdup(tmp);
			free(tmp);
		}
		else if ((size_t)f->precision > ft_strlen(str))
			f->precision = ft_strlen(str);
	}
	return (ft_strdup(str));
}

char	*check_precisionflag_p(t_printf *f, const char *str)
{
	int i;

	i = 0;
	if (f->flag_precision == 1)
	{
		if ((size_t)f->precision > ft_strlen(str))
		{
			i = 0;
			ft_print_charxtimes(f, '0', (f->precision - (int)ft_strlen(str)));
		}
	}
	return (ft_strdup(str));
}

void	check_precisionflag_u(t_printf *f, long int integer)
{
	int			len;
	long int	i;

	i = 0;
	if (f->flag_precision == 1)
	{
		len = f->precision - ft_intlen(integer);
		if (len < 0)
			len = 0;
		ft_print_charxtimes(f, '0', len);
	}
}

char	*check_precisionflag_x(t_printf *f, const char *str)
{
	int i;

	i = 0;
	if (f->flag_precision == 1)
	{
		if ((size_t)f->precision > ft_strlen(str))
		{
			i = 0;
			while (i < (f->precision - (int)ft_strlen(str)))
			{
				ft_putchar('0');
				f->len++;
				i++;
			}
		}
	}
	return (ft_strdup(str));
}
