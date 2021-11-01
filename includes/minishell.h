/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:46 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/01 14:18:20 by marcos           ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>
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


int		provisional_parser(t_general *g_minishell,char *command);
void	signals();
void	quitsignal(int sig);
void	executor(t_general *g_minishell,char **envp,int *pid);
char	*ft_findpath(char **envp);
char	*read_line(char *command);
void	ft_pruveaccess(char *cmd, int fd, char **mycmd, char **envp);
void	ft_parent(int fd2, char **mycmd2, char **envp, int *end);
void	ft_child(int fd1, char **mycmd1, char **envp, int *end);
char	**ft_parsepaths(char **envp);

# endif	
