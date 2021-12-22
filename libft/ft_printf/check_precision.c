/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 20:19:00 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/22 13:28:21 by marcos           ###   ########.fr       */
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
			ft_putchar_fd('-',f->fd);
			f->len++;
		}
		ft_print_charxtimes(f, '0', len);
	}
}

char	*check_precisionflag_s(t_printf *f, char *str)
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
	return (str);
}

char	*check_precisionflag_p(t_printf *f, char *str)
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
	return (str);
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

char	*check_precisionflag_x(t_printf *f, char *str)
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
				ft_putchar_fd('0',f->fd);
				f->len++;
				i++;
			}
		}
	}
	return (str);
}
