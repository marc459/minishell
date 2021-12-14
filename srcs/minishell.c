/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/12/14 17:34:02 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#if defined(__APPLE__)
# define SO "MACOS"

char	*read_line(char *prompt)
{
	char	*command;

	command = readline(prompt);
	if (command && *command)
		add_history (command);
	return (command);
}
#else
# define SO "LINUX"

char	*read_line(char *prompt)
{
	int	i;
	char *command;

	i = 0;
	command = ft_calloc(sizeof(char), 64);
	ft_putstr_fd(prompt,1);
	//scanf("%s");
	read(0,command,64);
	while (command[i])
	{
		if (command[i] == 10)
		{
			command[i] = '\0';
		}
		i++;
	}
	return (command);
}
#endif

void	checkleaks(void)
{
	system("leaks minishell >> leaks.txt");
}

void	exit_error(char **command)
{
	char	**freespaces;

	freespaces = ft_split(*command, ' ');
	if (freespaces[1] && !str_isnumber(freespaces[1]))
		printf("minishell: exit: 00-99: numeric argument required\n");
	else if (ft_bidstrlen(freespaces) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		*command = ft_strdup("noexit");
	}
	else if (ft_bidstrlen(freespaces) == 1 && (command[0][4] != '\0'
		&& command[0][4] != ' '))
	{
		printf("minishell: %s: command not found\n", command[0]);
		*command = ft_strdup("noexit");
	}
	ft_freebidstr(freespaces);
}

void	ft_prompt(t_general *g_m)
{
	pid_t	pid;
	char	*command;

	command = ft_calloc(sizeof(char), 64);
	while (command && ft_strncmp(command, "exit", 4))
	{		
		free(command);
		command = read_line(BEGIN(1, 49, 34)"Minishell-1.0:"CLOSE);
		if (command && ft_strncmp(command, "exit", 4) && command[0] != '\0')
		{
			ft_inigeneral(g_m);
			ft_parse(g_m, command);
			//ft_printgeneral(g_m);
			printf("%s< QUINES && MEXIL SHELL >%s\n\n", BCyan, Color_Off);
			ft_executor(g_m, g_m->ownenv, &pid);
			printf("%s< REAL BASH >%s\n\n", BCyan, Color_Off);
			system(command);
			free_gminishell(g_m);
		}
		else if (command && !ft_strncmp(command, "exit", 4))
			exit_error(&command);
	}
	free(command);
	ft_freebidstr(g_m->ownenv);
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	t_general	g_minishell;

	runcflag(g_minishell, environ, argv, pid);
	//signals();
	g_piperet = 0;
	g_minishell.ownenv = ft_ownenv(environ);
	ft_prompt(&g_minishell);
	printf("exit\n");
	//checkleaks();
	return (0);
}
