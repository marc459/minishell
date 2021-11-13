/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 22:32:27 by marcos            #+#    #+#             */
/*   Updated: 2021/11/13 22:00:51 by msantos-         ###   ########.fr       */
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
int		main(int argc,char **argv, char **envp)
{
	int		status;
	pid_t	pid;
	char	*command;
	char	*s;
	t_general g_minishell;
	char **comands;
	
	int i;
	
	
	if(argc > 1)
		return (-1);
	//signals();
	command = malloc(sizeof(char) * 64);
	ft_memset(command, '\0', 64);
	
	ft_inigeneral(&g_minishell);
	
	while (ft_strncmp(command, "exit",4))
	{
		i = 0;
		free(command);
		command = read_line(command);
		//command = ft_strdup("ls");
		//if(ft_strncmp(command, "exit",4) && ft_strncmp(command, "",1))
		//{
			//system("clear"); //
			//lexer && parser
			//comands = provisional_parser(&g_minishell,command);
			
			ft_parse(&g_minishell,command);
			//printf("Llegue\n");
			ft_printgeneral(&g_minishell);
			
			//system("leaks minishell");
			
			//Executor
			printf("%s< QUINES && MEXIL SHELL >%s\n\n",BCyan,Color_Off); //
			
			ft_executor(&g_minishell,envp,&pid);
			printf("%s< REAL BASH >%s\n\n",BCyan,Color_Off); //	
			//system(command); //
			//ft_freebidstr(comands);
			//free_gminishell(&g_minishell);
			ft_freeall(&g_minishell);
		//}
	}
	free(command);
	printf("exit\n");
	//system("leaks minishell");
	
	
	return (0);
}
