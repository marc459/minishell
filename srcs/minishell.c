/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/11/04 17:13:40 by msantos-         ###   ########.fr       */
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

int		main(int argc,char **argv, char **envp)
{
	int		status;
	pid_t	pid;
	char	*command;
	char	*s;
	t_general g_minishell;
	
	int i;
	
	if(argc > 1)
		return (-1);
	//signals();
	command = malloc(sizeof(char) * 64);
	ft_memset(command, '0', 64);
	while (ft_strncmp(command, "exit", ft_strlen(command)))
	{
		
		command = read_line(command);
		//lexer && parser
		system("clear");
		provisional_parser(&g_minishell,command);

		//Executor
		ft_printf("%s< QUINES && MEXIL SHELL >%s\n\n",BCyan,Color_Off);
		executor(&g_minishell,envp,&pid);
		ft_printf("%s< REAL BASH >%s\n\n",BCyan,Color_Off);
		system(command);
		free(command);
	}
	return (0);
}
