/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:05:45 by msantos-          #+#    #+#             */
/*   Updated: 2022/03/23 23:02:05 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_exec {
	char    *content;
	int     pipe[2];
}				t_exec;

typedef struct s_general
{
    t_exec	*exec;
    int     npipes;
    int     nexec;
    int     fdin;
	int	    fdout;
    int     nexec;
}				t_general;

void	administratepipe(int i, t_general *g)
{
	g->fdin = 0;
	g->fdout = 1;
	if (g->npipes > 0)
	{
		if (i == (int)(g->nexecutables - 1))
		{
			if (i > 1)
				close(g->exec[i - 2].pipe[READ_END]);
		}
	}
	if (i < (int)g->npipes)
		pipe(g->exec[i].pipe);
}


void	administratestds(int i, t_general *g)
{
	if (i == 0)
	{
		if (g->npipes > 0)
		{
			g->fdout = g->exec[i].pipe[WRITE_END];
			close(g->exec[i].pipe[READ_END]);
		}
	}
	else if (i == (int)(g->nexecutables - 1))
		g->fdin = g->exec[i - 1].pipe[READ_END];
	else
	{
		g->fdin = g->exec[i - 1].pipe[READ_END];
		g->fdout = g->exec[i].pipe[WRITE_END];
		close(g->exec[i].pipe[READ_END]);
	}
}

void	executecmd(t_general *g, char **cmd, char **envp, int i)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		administratestds(i, g);
		checkopenendfds(g);
		if (g->fdin >= 0 && g->fdout >= 0)
		{
			changestds(g);
			ft_child(cmd, envp, &g->fdout2);
		}
		exit (g_piperet);
	}
	else if (pid < 0)
		printf("Error\n");
}

char	*ft_strdup(const char *s1)
{
	char	*n;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	i = -1;
	len = ft_strlen(s1);
	n = (char *)malloc(sizeof(char) * (len + 1));
	if (n == NULL)
		return (NULL);
	while (++i < len)
		n[i] = s1[i];
	n[i] = '\0';
	return (n);
}


void	ft_child(char **fullcmd, char **envp, int *stdo)
{
	char	*cmd;
	size_t	i;

	i = 0;
	if (ft_strchr(fullcmd[0], '/'))
	{
		cmd = ft_strdup(fullcmd[0]);
		if (!access(cmd, X_OK))
			execve(cmd, fullcmd, envp);
		free(cmd);
	}
	printf("Minishell: %s command not found\n", fullcmd[0]);
}

void	waitforthem(t_general *g, int nchilds)
{
	int	i;
	int	j;

	i = 0;
	while (i < nchilds)
	{
		waitpid(g->pids[i], &j, 0);
		i++;
	}
	if (g->fdin > 1)
		close(g->fdin);
}

void	closefds(t_general *g, int i)
{
	if (i > 0 && g->npipes > 0)
		close(g->exec[i - 1].pipe[READ_END]);
	if (i < (int)g->npipes)
		close(g->exec[i].pipe[WRITE_END]);
	if (g->fdout > 1)
		close(g->fdout);
	if (g->fdin > 1)
		close(g->fdin);
}

int	ft_bidstrlen(char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (s1 && !s2)
		return (1);
	if (!s1 && s2)
		return (-1);
	if (!s1 && !s2)
		return (0);
	i = -1;
	while (++i < n && s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
	}
	if (i < n)
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
	}
	return (0);
}

static size_t	ft_count_words(char const *s, size_t *i, char c)
{
	size_t	cont_str;
	size_t	find_let;

	cont_str = 0;
	find_let = 0;
	while (s[++*i] != '\0')
	{
		if ((s[*i] == c) && (*i > 0) && (find_let > 0))
		{
			cont_str++;
			find_let = 0;
		}
		else if (s[*i] != c)
			find_let++;
	}
	if (find_let > 0)
		cont_str++;
	return (cont_str);
}

static char	**ft_fill_split(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	palabra;

	i = -1;
	j = 0;
	k = 0;
	palabra = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			palabra++;
			split[j][k++] = s[i];
		}
		else if (palabra > 0)
		{
			split[j++][k] = '\0';
			k = 0;
			palabra = 0;
		}
	}
	return (split);
}

static void	ft_asign(size_t *i, size_t *j, size_t a, size_t b)
{
	*i = a;
	*j = b;
}

char	**ft_split(char const *s, char c)
{
	size_t	index[3];
	size_t	cont_str;
	char	**split;

	if (!s)
		return (NULL);
	ft_asign(&index[0], &index[1], -1, 0);
	split = ft_calloc((ft_count_words(s, &index[0], c) + 1), sizeof(char *));
	ft_asign(&index[2], &index[0], index[0] + 1, -1);
	if (!split)
		return (NULL);
	cont_str = 0;
	while (++index[0] < index[2])
	{
		if (s[index[0]] != c && s[index[0]] != '\0')
			cont_str++;
		else
		{
			if (cont_str > 0)
				split[index[1]++] = ft_calloc((cont_str + 1), sizeof(char));
			cont_str = 0;
		}
	}
	return (ft_fill_split(split, s, c));
}


void    ft_executor(t_general *g,  char **commands, char **envp)
{
    int		i;
	char	**cm;

    i = -1;
	while (++i < (int)g->nexec)
	{
		administratepipe(i, g);
		cm = commands[i];
		if (cm[0])
			executecmd(g, cm, envp, i);
		closefds(g, i);
	}
	waitforthem(g, g->nexec);
    
}
void ft_initargs(t_general *g,  char **commands, argv)
{
    int		i;
    int j;

	i = -1;
    g->nexec = 0;
    while(++i < ft_bidstrlen(argv))
    {
        if(ft_strncmp("|",commands[i],2))
        {
            g->nexec++;
        }
    }
    g->exec = ft_calloc(sizeof(t_exec), (g->nexec + 1));
    i = -1;
    j = 0;
    while(++i < ft_bidstrlen(argv))
    {
        if(ft_strncmp("|",commands[i],2))
        {
            g->nexec[j].content = commands[j];
            j++;
        }
    }
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;
	char	*final;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	final = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (final == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		final[i] = s1[i];
	while (s2[++j] != '\0')
		final[i + j] = s2[j];
	final[i + j] = '\0';
	return (final);
}


int     main(int argc, char **argv, char **envp)
{
    t_general g;
    int		i = 0;
    int        j = 0;
    char        **commands;
    
    while(++i < argc -1 && ft_strncmp(";",argv[i],2)
    {
            j++;
    }
    commads = sizeof(char*) * j;
    i = 0;
    while(++i < argc -1 && ft_strncmp(";",argv[i],2)
    {
        commands[i] = ft_strdup(argv[i]);
    }
    
    ft_initargs(&g, commands);
    ft_executor(&g, commands, envp);

    
    return (0);
}