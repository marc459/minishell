/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:26:09 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/01 14:52:13 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*typedef struct s_arg {
	size_t	type;
	char	*content;
}			t_arg;

typedef struct s_general {
	size_t	npipes;
	size_t	ncomands;
	size_t	nredirections;
	t_arg	*args;
}			t_general;*/


//Divides command line in (command,file,pipe,expansion)
int		provisional_parser(t_general *g_minishell,char *command)
{
	/*char	**commands;
	int i;

	i = 0;
	commands = ft_split(command,' ');
	while(commands[i])
	{
		ft_printf("%s\n",commands[i]);
		i++;
	}*/
	
	// ls | wc
	
	g_minishell->npipes = 1;
	g_minishell->ncomands = 2;
	g_minishell->nredirections = 0;
	g_minishell->args = malloc(sizeof(t_arg) * (g_minishell->ncomands + g_minishell->npipes));

	g_minishell->args[0].content = "ls";
	g_minishell->args[0].type = 3;
	g_minishell->args[1].content = "|";
	g_minishell->args[1].type = 5;
	g_minishell->args[2].content = "wc";
	g_minishell->args[2].type = 3;

	return(1);
}