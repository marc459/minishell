/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 21:56:51 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/24 01:09:46 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*dec_to_hex_p(unsigned long int num)
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
		hex[i] = rem < 10 ? (char)rem + 48 : (char)rem + 55;
		num /= 16;
		i++;
	}
	hex[i] = '\0';
	i = 0;
	return (ft_strdup(ft_strrev(hex)));
}

void	checkflags_p(t_printf *f, int num, char *string)
{
	if (f->flag_precision == 1 && f->precision == 0 && num == 0)
	{
		string = ft_strdup("");
		check_widthflag_p(f, string);
		ft_putstrcounter("0x", f);
	}
	else if (f->flag_minus == 1)
	{
		ft_putstrcounter("0x", f);
		string = check_precisionflag_p(f, string);
		ft_putstrcounter(string, f);
		check_widthflag_p(f, string);
	}
	else
	{
		check_zeroflag_p(f, string);
		check_widthflag_p(f, string);
		ft_putstrcounter("0x", f);
		string = check_precisionflag_p(f, string);
		ft_putstrcounter(string, f);
	}
}

void	print_ptr(t_printf *f)
{
	char				*string;
	unsigned long int	num;
	int					i;

	i = -1;
	num = va_arg(f->ap, unsigned long int);
	string = dec_to_hex_p(num);
	while (string[++i])
		string[i] = ft_tolower(string[i]);
	checkflags_p(f, num, string);
}
