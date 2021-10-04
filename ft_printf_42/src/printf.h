/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/24 01:53:19 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include "../../libft_42/libft.h"

typedef	struct	s_printf
{
	va_list		ap;
	int			len;
	int			i;
	int			flag_minus;
	int			flag_zero;
	int			flag_width;
	int			flag_precision;
	int			width;
	int			precision;
}				t_printf;

int				ft_printf(const char *format, ...);
void			initialize_flags(t_printf *f);
void			flag_sorting(const char *format, t_printf *f);
void			variable_sorting(const char *format, t_printf *f);
void			print_integer(t_printf *f);
void			ft_putstrcounter(const char *s, t_printf *f);
void			print_string(t_printf *f);
void			check_widthflag_s(t_printf *f, char *str);
char			*check_precisionflag_s(t_printf *f, const char *str);
void			print_character(t_printf *f);
void			check_widthflag_c(t_printf *f);
void			print_hexadecimal(t_printf *f, const char *format);
void			print_ptr(t_printf *f);
void			print_0(t_printf *f);
void			print_unsigned(t_printf *f);
void			ft_print_charxtimes(t_printf *f, char c, int x);
void			check_widthflag_i(t_printf *f, int integer);
void			check_widthflag_s(t_printf *f, char *str);
void			check_widthflag_p(t_printf *f, char *str);
void			check_widthflag_u(t_printf *f, long int integer);
void			check_widthflag_x(t_printf *f, char *str);
void			check_precisionflag_i(t_printf *f, int integer);
char			*check_precisionflag_s(t_printf *f, const char *str);
char			*check_precisionflag_p(t_printf *f, const char *str);
void			check_precisionflag_u(t_printf *f, long int integer);
char			*check_precisionflag_x(t_printf *f, const char *str);
void			check_zeroflag_i(t_printf *f, int integer);
void			check_zeroflag_p(t_printf *f, char *str);
void			check_zeroflag_u(t_printf *f, long int integer);
void			check_zeroflag_x(t_printf *f, char *str);

#endif
