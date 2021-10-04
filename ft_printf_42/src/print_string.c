/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:18:15 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/24 01:09:54 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	print_string(t_printf *f)
{
	char *string;

	string = (char *)va_arg(f->ap, char *);
	if (f->precision == 0 && f->flag_precision == 1)
		string = "";
	if (string == NULL)
		string = "(null)";
	if (f->flag_minus == 1 || (f->width < 0 && f->flag_width == 1))
	{
		if (f->width < 0)
			f->width = f->width * (-1);
		string = check_precisionflag_s(f, string);
		ft_putstrcounter(string, f);
		check_widthflag_s(f, string);
	}
	else
	{
		string = check_precisionflag_s(f, string);
		check_widthflag_s(f, string);
		ft_putstrcounter(string, f);
	}
}
