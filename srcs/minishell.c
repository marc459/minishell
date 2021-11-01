/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/11/01 14:43:27 by marcos           ###   ########.fr       */
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
	int status;
	pid_t	pid;
	char	*command;
	char *s;
	t_general g_minishell;
	
	int i;
	
	if(argc > 1)
		return (-1);
	signals();
	command = malloc(sizeof(char) * 64);
	ft_memset(command, '\0', 64);
	command = read_line(command);
	
	while (ft_strncmp(command, "exit", ft_strlen(command)))
	{
		pid = fork();
		if (pid == 0)
		{
			//lexer
			printf("child\n");
			provisional_parser(&g_minishell,command);
			//Parser

			//Executor
			
			executor(&g_minishell,envp,&pid);							
			execlp(command, command, NULL); 
			ft_printf("Quineshell: %s: command not found\n",command);
			free(command);
			exit(0);
		}
		else
		{
			if (pid > 0)
			{
				wait(&status);
				//command = readline("Quineshell-1.0:");
				//add_history (command);
				//scanf("%s",command);
				command = read_line(command);
			}
			else
				ft_printf("Error Fork\n");
		}
	}
	return (0);
}
