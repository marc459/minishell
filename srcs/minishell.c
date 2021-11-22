/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/11/22 20:26:42 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#if defined(__APPLE__)
# define SO "MACOS"

char	*read_line(char *command)
{
	free(command);
	command = readline("Quineshell-1.0:");
	add_history (command);
	return (command);
}
#else
# define SO "LINUX"

char	*read_line(char *command)
{
	int	i;

	i = 0;
	ft_putstr_fd("Quineshell-1.0:",1);
	//scanf("%s");
	read(0,command,64);
	printf("faf\n");
	while (command[i])
	{
		if (command[i] == 10)
		{
			command[i] = '\0';
		}
		i++;
	}
	printf("cmd:%s;\n",command);
	return (command);
}
#endif

void	hola(void)
{
	system("leaks minishell");
}

void	free_gminishell(t_general *g_minishell)
{
	free(g_minishell->args);
}

void	exit_error(char **command)
{
	char **freespaces;
	freespaces = ft_split(*command,' ');
	if(freespaces[1] && !str_isnumber(freespaces[1]))
		printf("minishell: exit: 00-99: numeric argument required\n");
	else if(ft_bidstrlen(freespaces) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		*command =ft_strdup("noexit");
	}
		
}

void	ft_prompt(t_general *g_m, char **environ)
{
	pid_t		pid;
	char		*command;

	command = ft_calloc(sizeof(char), 64);
	while (ft_strncmp(command, "exit", 4))
	{
		ft_inigeneral(g_m);
		command = read_line(command);
		if (ft_strncmp(command, "exit", 4) && ft_strncmp(command, "", 1))
		{
			//system("clear");
			ft_parse(g_m, command);
			ft_printgeneral(g_m);
			printf("%s< QUINES && MEXIL SHELL >%s\n\n", BCyan, Color_Off);
			ft_executor(g_m, environ, &pid);
			printf("%s< REAL BASH >%s\n\n", BCyan, Color_Off);
			//system(command);
		}
		else
			exit_error(&command);
	}
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	t_general	g_minishell;

	runcflag(g_minishell, environ, argv, pid);
	//signals();
	ft_prompt(&g_minishell, environ);
	printf("exit\n");
	return (0);
}
