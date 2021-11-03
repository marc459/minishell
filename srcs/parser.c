/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:26:09 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/03 23:51:20 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Divides command line in (command,file,pipe,expansion)
int		provisional_parser(t_general *g_minishell,char *command)
{
	int i;

	i = 0;
	
	// ls | wc
	
	g_minishell->npipes = 3;
	g_minishell->ncomands = 4;
	g_minishell->nredirections = 0;
	g_minishell->args = malloc(sizeof(t_arg) * (g_minishell->ncomands + g_minishell->npipes));

	g_minishell->args[0].content = "ls";
	g_minishell->args[0].type = 3;
	g_minishell->args[1].content = "|";
	g_minishell->args[1].type = 5;
	g_minishell->args[2].content = "ls";
	g_minishell->args[2].type = 3;
	g_minishell->args[3].content = "|";
	g_minishell->args[3].type = 5;
	g_minishell->args[4].content = "ls";
	g_minishell->args[4].type = 3;
	g_minishell->args[5].content = "|";
	g_minishell->args[5].type = 5;
	g_minishell->args[6].content = "wc";
	g_minishell->args[6].type = 3;
	//system("pwd");
	printf("G_MINISHELL\n");
	printf("  n_pipes: %zu\n",g_minishell->npipes);
	printf("  n_comands: %zu\n",g_minishell->ncomands);
	printf("  n_redireccions: %zu\n\n",g_minishell->nredirections);
	while(i < (g_minishell->ncomands + g_minishell->npipes))
	{
		printf("\tCMD\n");
		printf("\t  content: %s\n",g_minishell->args[i].content);
		printf("\t  type: %zu\n",g_minishell->args[i].type);
		i++;
	}

	return(1);
}