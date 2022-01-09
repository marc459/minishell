/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:46 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/09 13:25:12 by marcos           ###   ########.fr       */
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
# include "../libft/ft_printf/printf.h"
# include "bashcolors.h"

# define READ_END    0
# define WRITE_END   1
# define CLOSE "\001\033[0m\002"
# define BEGIN "\001\033[1;49;34m\002"

typedef struct s_arg {
	size_t	type;
	char	**content;
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

typedef struct s_general {
	size_t	npipes;
	int		nexecutables;
	size_t	ncommands;
	size_t	nredirections;
	t_arg	*args;
	t_exec	*exec;
	char	*heredockcontent;
	int		fdin;
	int		fdout;
	int		fdincpy;
	int		fdoutcpy;
	int		fdout2;
	int		quot;
	int		dquot;
	char	**ownenv;
	t_parse	parse;
	size_t	argssize;
	int		*pospipes;
}			t_general;

int	g_piperet;

void	sig_main(void);
void	sig_heredock(void);
void	sig_ignore(void);
void	sig_child(void);
void	quitsignal(int sig);
void	ft_executor(t_general *g_minishell, char **envp);
char	*ft_findpath(char **envp);
char	*read_line(char *command);
void	ft_child(char **fullcmd, char **envp, int *stdo);
char	**ft_parsepaths(char **envp);
void	define_fds(t_general *g, int i, int x, int y);
void	administratepipe(int i, t_general *g_mini);
void	administratestds(int i, t_general *g_mini);
void	waitforthem(int *childpid, int nchilds);
void	leakatexit(void);
void	runcflag(t_general	*g_mini, char **environ, char **argv);
void	ft_parsebuiltin(t_general *g_mini, char **cmd, int i);
char	*ft_dropquotes(t_general *g, char *str);
void	ft_checknewenv(t_general *g, char *newenv);
size_t	ft_checkenvname(char *name);
void	ft_remenv(t_general *g, char *remenv);
void	ft_printsortenv(char **ownenv);
char	*ft_dropexportquotes(t_general *g, char *str);
void	heredock(t_general *g_mini, int i);
void	define_fds2(t_general *g_mini, int exec, int i);
size_t	ft_error(size_t ncomands, size_t i, char **cmds);
char	**ft_dropkeyvalue(char *str, int quote, int dquote);
size_t	ft_splitfindchar(char **split, char c);
size_t	ft_ignorespace(size_t i, char *str);
void	createtmpfile(t_general *g_mini);
void	commandoutput(int ret);
void	executecmd(t_general *g_mini, char **cmd, char **envp, int i);
void	exit_error(char **command);
void	ft_echo(char **cmd);
void	heredock2(t_general *g_mini, int i, char **tmp);
void	openfiles(t_general *g, int i);
void	closefds(t_general *g_mini, int i);
void	changestds(t_general *g);
void	givebackstds(t_general *g);
void	ft_checkleaksreturn(void);
size_t	ft_isspar(char *str);
void	checkopenendfds(t_general *g_mini);
size_t	ft_errorfinalarg(void);
void	ft_cd(t_general *g, char *path);
void	ft_putbidstr(char **str);

char	*ft_dropspace(char *str);
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
t_arg	*ft_copycleanargs(t_general *g, size_t newargs);
void	ft_freecontent(t_arg *args, size_t argssize);
void	ft_countthings(t_general *g);
char	*ft_cutstr(char *str);
size_t	ft_countcut(char *str);
size_t	ft_findchar(char *str, char c);
int		str_isnumber(char *str);
void	free_gminishell(t_general *g_minishell);
void	ft_refactquotes(t_general *g);
void	ft_expvar(t_general *g);
char	**ft_ownenv(char **environ);
void	ft_checkquotes(t_general *g);
void	checkleaks(void);

#endif
