/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/11/15 21:07:32 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# if defined(__APPLE__)
	#	define SO "MACOS"

	char *read_line(char *command)
	{
		command = readline("Quineshell-1.0:");
		add_history (command);
		return(command);
	}
# else
	#	define SO "LINUX"
	char *read_line(char *command)
	{	
		int i;

		i= 0;
		//scanf("%s",command);
		while(command[i])
		{
			if(command[i]== 10)
			{
				command[i] = '\0';
			}
			i++;
		}
		//command[2]= '\0';
		return(command);
	}
# endif

void	hola(void)
{
	system("leaks minishell");
}

void	free_gminishell(t_general *g_minishell)
{
	free(g_minishell->args);
}

void	ft_prompt(t_general *g_m, char **environ)
{
	pid_t		pid;
	char		*command;

	command = calloc(sizeof(char), 64);
	command = read_line(command);
	while (ft_strncmp(command, "exit", 5))
	{
		ft_inigeneral(g_m);
		if (ft_strncmp(command, "exit", 5) && ft_strncmp(command, "", 1))
		{
			system("clear");
			ft_parse(g_m, command);
			printf("%s< QUINES && MEXIL SHELL >%s\n\n", BCyan, Color_Off);
			ft_executor(g_m, environ, &pid);
			printf("%s< REAL BASH >%s\n\n", BCyan, Color_Off);
			system(command);
			ft_freeall(g_m);
		}
		free(command);
		command = read_line(command);
	}
	free(command);
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	int			status;
	t_general	g_minishell;

	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		ft_inigeneral(&g_minishell);
		if (ft_strncmp(argv[2], "exit", 5) && ft_strncmp(argv[2], "", 1))
		{
			ft_parse(&g_minishell, argv[2]);
			ft_executor(&g_minishell, environ, &pid);
			ft_printgeneral(&g_minishell);
			ft_freeall(&g_minishell);
		}
		return (0);
	}
	if (argc > 1)
		return (-1);
	signals();
	ft_prompt(&g_minishell, environ);
	printf("exit\n");
	return (0);
}
