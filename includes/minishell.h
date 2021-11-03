/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:46 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/03 22:44:03 by msantos-         ###   ########.fr       */
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

#define READ_END    0
#define WRITE_END   1


typedef struct s_arg {
	size_t	type;
	char	*content;
}			t_arg;

typedef struct s_exec {
	int	posexec;
	int pipe[2];
	int fd[2];
	int *fdin;
	int *fdout;
	int *closedfd;
	int pos; // 1 -> first executable 2 - executable beween pipes 3- last executable
}				t_exec;
typedef struct s_general {
	size_t	npipes;
	size_t	ncomands;
	size_t	nredirections;
	t_arg	*args;
	t_exec	*exec;
}			t_general;


int		provisional_parser(t_general *g_minishell,char *command);
void	signals();
void	quitsignal(int sig);
void	executor(t_general *g_minishell,char **envp,int *pid);
char	*ft_findpath(char **envp);
char	*read_line(char *command);
void	ft_pruveaccess(char *cmd, char **mycmd, char **envp);
void	ft_parent(int fd2,int pid, char **mycmd2, char **envp, int *end);
void	ft_child(int *fdin,int *fdout, char **mycmd1, char **envp, int *stdo);
char	**ft_parsepaths(char **envp);
void	ft_child2(int *fd, int pid, char **mycmd2, char **envp, int *end);

# endif	
