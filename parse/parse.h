/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:11:27 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/26 21:35:24 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_parse
{
	int		quot;
	int		dquot;
	size_t	comand;
	size_t	comndssize;
}			t_parse;

typedef struct s_arg {
	size_t	type;
	char	*content;
}			t_arg;

typedef struct s_general {
	size_t	npipes;
	size_t	ncomands;
	size_t	nredirections;
	t_arg	*args;
}			t_general;

void	leak(void);

void	ft_parse(char *str, t_general *general);
void	ft_inigeneral(t_general *general);
size_t	ft_findspchar(char *str);
size_t	ft_spchar(char c);
void	ft_printgeneral(t_general *general);
void	ft_inigeneral(t_general *general);

#endif
