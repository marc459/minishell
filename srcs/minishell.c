/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/11/09 19:42:23 by msantos-         ###   ########.fr       */
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
		printf("Quineshell-1.0:");
		scanf("%s",command);
		return(command);
	}
# endif
void	hola()
{
	system("leaks minishell");
}

int		main(int argc,char **argv, char **envp)
{
	//atexit(hola);
	int		status;
	pid_t	pid;
	char	*command;
	char	*s;
	t_general g_minishell;
	
	int i;
	
	i = 0;
	if(argc > 1)
		return (-1);
	signals();
	command = malloc(sizeof(char) * 64);
	ft_memset(command, '\0', 64);
	while (ft_strncmp(command, "exit",4))
	{
		free(command);
		command = read_line(command);
		if(ft_strncmp(command, "exit",4) && ft_strncmp(command, "",1))
		{
			
			system("clear"); //
			//lexer && parser
			provisional_parser(&g_minishell,command);
			while(command[i])
			{
				if(command[i] == '_')
					command[i] = ' ';
				i++;
			}
	
			//Executor
			ft_printf("%s< QUINES && MEXIL SHELL >%s\n\n",BCyan,Color_Off); //
			ft_executor(&g_minishell,envp,&pid);
			ft_printf("%s< REAL BASH >%s\n\n",BCyan,Color_Off); //
			system(command); //
		}
	}
	free(command);
	ft_printf("exit\n");
	return (0);
}
