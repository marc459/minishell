/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/11/22 22:52:16 by msantos-         ###   ########.fr       */
/*   Updated: 2021/11/22 21:58:22 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#if defined(__APPLE__)
# define SO "MACOS"

char	*read_line(char *command)
{
	//free(command);
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
	free(freespaces);
		
}
void	checkquotes(t_general *g_m, char *command)
{
	char		*tmp;
	char		*tmp2;

	tmp2 = ft_calloc(sizeof(char), 64);
	while(g_m->dquot == -1 || g_m->quot == -1)
	{
		free(tmp2);
		free_gminishell(g_m);
		ft_inigeneral(g_m);
		tmp = readline(">");
		tmp2 = ft_strjoin(command, tmp);
		ft_parse(g_m, tmp2);
		ft_printgeneral(g_m);
		
	}
	add_history (tmp2);
	free(tmp2);
	
	
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
			checkquotes(g_m, command);
			
			printf("%s< QUINES && MEXIL SHELL >%s\n\n", BCyan, Color_Off);
			ft_executor(g_m, environ, &pid);
			printf("%s< REAL BASH >%s\n\n", BCyan, Color_Off);
			//system(command);
		}
		else
			exit_error(&command);
		free_gminishell(g_m);
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
