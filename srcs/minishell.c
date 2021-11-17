/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/11/17 16:03:33 by msantos-         ###   ########.fr       */
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
void	hola()
{
	system("leaks minishell");
}
void	free_gminishell(t_general *g_minishell)
{
	free(g_minishell->args);
}

void	exit_error(char *command)
{
	char **freespaces;
	freespaces = ft_split(command,' ');
	if(freespaces[1] && (!str_isnumber(freespaces[1]) || ft_bidstrlen(freespaces) > 2))
		printf("minishell: exit: 00-99: numeric argument required\n");
}
int		main(int argc,char **argv, char **envp)
{
	int		status;
	pid_t	pid;
	char	*command;
	char	*s;
	t_general g_minishell;
	

	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		ft_inigeneral(&g_minishell);
		if(ft_strncmp(argv[2], "exit",4) && ft_strncmp(argv[2], "",1))
		{
			ft_parse(&g_minishell,argv[2]);
			ft_executor(&g_minishell,envp,&pid);
			ft_freeall(&g_minishell);
		}
		else
			exit_error(argv[2]);
		return (0);
	}

	if(argc > 1)
		return (-1);
	
	signals();
	command = calloc(sizeof(char), 64);

	while (ft_strncmp(command, "exit",4))
	{
		free(command);
		command = read_line(command);
		ft_inigeneral(&g_minishell);
		if(ft_strncmp(command, "exit",4) && ft_strncmp(command, "",1))
		{
			system("clear"); //
			//lexer && parser
			ft_parse(&g_minishell,command);
			ft_printgeneral(&g_minishell);
			//system("leaks minishell");
			//Executor
			printf("%s< QUINES && MEXIL SHELL >%s\n\n",BCyan,Color_Off); //
			ft_executor(&g_minishell,envp,&pid);
			//printf("%s< REAL BASH >%s\n\n",BCyan,Color_Off); //	
			//system(command); //
			ft_freeall(&g_minishell);
		}
		else
			exit_error(command);
	}
	free(command);
	printf("exit\n");

	return (0);
}
