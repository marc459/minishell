/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:46 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/10 20:20:46 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <sys/uio.h>
# include <fcntl.h>
#include "../readline/readline.h"
#include "../readline/history.h"
#include "../ft_printf_42/src/printf.h"
#include "../libft_42/libft.h"
#include "bashcolors.h"


#define READ_END    0
#define WRITE_END   1


typedef struct s_arg {
	size_t	type;
	char	*content;
}			t_arg;

typedef struct s_exec {
	int	posexec;
	int pipe[2];
}				t_exec;
typedef struct s_general {
	size_t	npipes;
	size_t	ncomands;
	size_t	nredirections;
	t_arg	*args;
	t_exec	*exec;
	int		fdin;
	int		fdout;
}			t_general;


char **provisional_parser(t_general *g_minishell,char *command);
void	signals();
void	quitsignal(int sig);
void	ft_executor(t_general *g_minishell,char **envp,int *pid);
char	*ft_findpath(char **envp);
char	*read_line(char *command);
void	ft_pruveaccess(char *cmd, char **mycmd, char **envp);
void	ft_parent(int fd2,int pid, char **mycmd2, char **envp, int *end);
void	ft_child(char **mycmd1, char **envp,int *stdi, int *stdo);
char	**ft_parsepaths(char **envp);
void	ft_child2(int *fd, int pid, char **mycmd2, char **envp, int *end);

# endif	
