/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_sorting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 19:51:28 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 00:20:25 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	variable_sorting(const char *format, t_printf *f)
{
	if (format[f->i] == 'c')
		print_character(f);
	else if (format[f->i] == 's')
		print_string(f);
	else if (format[f->i] == 'p')
		print_ptr(f);
	else if (format[f->i] == 'd' || format[f->i] == 'i')
		print_integer(f);
	else if (format[f->i] == 'u')
		print_unsigned(f);
	else if (format[f->i] == 'x' || format[f->i] == 'X')
		print_hexadecimal(f, format);
	else if (format[f->i] == '%')
		print_0(f);
}
