/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:52:35 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/23 23:22:39 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	initialize_flags(t_printf *f)
{
	f->flag_minus = 0;
	f->flag_width = 0;
	f->flag_precision = 0;
	f->flag_zero = 0;
	f->width = 0;
	f->precision = 0;
}
