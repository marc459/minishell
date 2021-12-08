/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:46 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/08 15:17:23 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "../readline/readline.h"
# include "../readline/history.h"
# include "../libft/libft.h"
# include "bashcolors.h"

# define READ_END    0
# define WRITE_END   1
# define CLOSE "\001\033[0m\002"
# define BEGIN(x, y, z) "\001\033["#x";"#y";"#z"m\002"

typedef struct s_arg {
	size_t	type;
	char	*content;
}			t_arg;

typedef struct s_exec {
	int	posexec;
	int	pipe[2];
}				t_exec;

typedef struct s_parse
{
	char	**comnds;
	size_t	comndssize;
	size_t	comand;
}			t_parse;

typedef struct s_env
{
	char	*envvar;
	char	*content;
	struct s_env *next;
	struct s_env *back;
}			t_env;

typedef struct s_general {
	size_t	npipes;
	size_t	nexecutables;
	size_t	nsemicolons;
	size_t	ncommands;
	size_t	nredirections;
	t_arg	*args;
	t_exec	*exec;
	char	*heredockcontent;
	int		fdin;
	int		fdout;
	int		quot;
	int		dquot;
	int		piperet;
	char	**ownenv;
	t_parse	parse;
	size_t	argssize;
	t_env	*varenvs;
}			t_general;

void	signals(void);
void	quitsignal(int sig);
void	ft_executor(t_general *g_minishell, char **envp, int *pid);
char	*ft_findpath(char **envp);
char	*read_line(char *command);
void	ft_child(char **fullcmd, char **envp, int *stdo);
char	**ft_parsepaths(char **envp);
void	define_fds(t_general *g_mini);
void	administratepipe(int i, t_general *g_mini);
void	administratestds(int i, t_general *g_mini);
void	waitforthem(int *childpid, int nchilds);
void	leakatexit(void);
void	runcflag(t_general	g_minishell, char **environ, char **argv, int pid);
t_env	*ft_envnew(char	*envvar, char *content);
void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envlast(t_env *lst);
void	ft_printsortenv(char **ownenv);
void	ft_orderenv(t_env **lst);
void	bubbleSort(t_env *start);
void	swapenv(t_env *a, t_env *b);
int		ft_envsize(t_env *lst);
void	ft_parsebuiltin(t_general *g_mini, char **cmd);
void	ft_checkenv(t_env **varenvs, char *keyvar, char *valuevar);
void	ft_envadd_front(t_env **lst, t_env *new);
void	ft_deleteenv(t_env **varenvs, char *keyvar);
char	*ft_dropquotes(t_general *g, char *str);
void	ft_checknewenv(t_general *g, char *newenv);
size_t	ft_checkenvname(char *name);
void	ft_remenv(t_general *g, char *remenv);

void	leak(void);
void	ft_parse(t_general *general, char *str);
void	ft_inigeneral(t_general *general);
size_t	ft_findspchar(char *str);
size_t	ft_spchar(char c);
void	ft_printgeneral(t_general *general);
void	ft_inigeneral(t_general *general);
void	ft_iniargs(t_general *g);
void	ft_freeall(t_general *g);
size_t	ft_contsp(t_general *g, size_t i);
void	ft_iniarg(t_general *g, size_t *j, char *str);
void	ft_refacttypes(t_general *g);
void	ft_freedouble(char **split);
t_arg	*ft_copycleanargs(t_general *g);
void	ft_freecontent(t_arg *args, size_t argssize);
void	ft_countthings(t_general *g);
char	*ft_cutstr(char *str);
size_t	ft_countcut(char *str);
size_t	ft_findchar(char *str, char c);
int		str_isnumber(char *str);
void	free_gminishell(t_general *g_minishell);
void	ft_refactquotes(t_general *g);
void	ft_expvar(t_general *g);
void	ft_cd(char	***env, char *path);
char	**ft_ownenv(char **environ);
void	ft_checkquotes(t_general *g);

#endif
