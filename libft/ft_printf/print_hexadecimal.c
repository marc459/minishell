/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadecimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 18:16:30 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/11 18:47:54 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*dec_to_hex(unsigned int num)
{
	int		rem;
	int		i;
	char	hex[100];

	rem = 0;
	i = 0;
	if (num == 0)
	{
		hex[0] = '0';
		i++;
	}
	while (num > 0)
	{
		rem = num % 16;
		num /= 16;
		i++;
	}
	hex[i] = '\0';
	i = 0;
	return (ft_strdup(ft_strrev(hex)));
}

void	checkflags_x(t_printf *f, int num, char *string)
{
	if (f->flag_precision == 1 && f->precision == 0 && num == 0)
	{
		check_zeroflag_x(f, string);
		check_widthflag_x(f, string);
		if ((f->flag_width == 1 || f->flag_zero == 1) && f->width > 0)
		{
			ft_putchar_fd(' ', f->fd);
			f->len++;
		}
	}
	else if (f->flag_minus == 1 || f->width < 0)
	{
		ft_putstrcounter(check_precisionflag_x(f, string), f);
		check_widthflag_x(f, string);
		f->flag_precision = 1;
		check_zeroflag_x(f, string);
	}
	else
	{
		check_zeroflag_x(f, string);
		check_widthflag_x(f, string);
		ft_putstrcounter(check_precisionflag_x(f, string), f);
	}
}

void	print_hexadecimal(t_printf *f, const char *format)
{
	char			*string;
	unsigned int	num;
	int				i;

	i = 0;
	num = va_arg(f->ap, unsigned int);
	string = dec_to_hex(num);
	if (format[f->i] == 'x')
	{
		while (string[i])
		{
			string[i] = ft_tolower(string[i]);
			i++;
		}
	}
	if (string == NULL)
		string = "(null)";
	checkflags_x(f, num, string);
}
