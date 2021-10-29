/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:46 by msantos-          #+#    #+#             */
/*   Updated: 2021/10/29 23:04:42 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "../readline/readline.h"
#include "../readline/history.h"
#include "../ft_printf_42/src/printf.h"
#include "../libft_42/libft.h"


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


int		parser(char *command);
void	signals();
void	quitsignal(int sig);
void	executor(char **envp);
char	*ft_findpath(char **envp);
char *read_line(char *command);

# endif	
