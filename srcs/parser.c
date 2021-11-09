/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:26:09 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/09 18:21:35 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Divides command line in (command,file,pipe,expansion)
int		provisional_parser(t_general *g_minishell,char *command)
{
	int i,x,y,pos;
	char **comands;

	
	i = 0;
	x= 0;
	y=0;
	pos = 0;
	
	
	// ls | wc
	g_minishell->npipes = 0;
	g_minishell->ncomands = 0;
	g_minishell->nredirections = 0;
	comands = ft_split(command, ' ');

	while (command[i])
	{
		if(command[i] == '|')
			g_minishell->npipes++;
		i++;
	}
	i = 0;
	g_minishell->ncomands = g_minishell->npipes + 1;
	g_minishell->args = malloc(sizeof(t_arg) * (g_minishell->ncomands + g_minishell->npipes));
	while(i < g_minishell->ncomands)
	{
		while(comands[pos][y])
		{
			if(comands[pos][y] == '_')
				comands[pos][y] = ' ';
			y++;
		}
		g_minishell->args[pos].content = comands[pos];
		g_minishell->args[pos].type = 3;
		pos++;
		if(x < g_minishell->ncomands)
		{
			
			g_minishell->args[pos].content = comands[pos];
			g_minishell->args[pos].type = 5;
			x++;
			pos++;
		}
		i++;	
	}

	i = 0;
	/*printf("G_MINISHELL\n");
	printf("  n_pipes: %zu\n",g_minishell->npipes);
	printf("  n_comands: %zu\n",g_minishell->ncomands);
	printf("  n_redireccions: %zu\n\n",g_minishell->nredirections);
	while(i < (g_minishell->ncomands + g_minishell->npipes))
	{
		printf("\tCMD\n");
		printf("\t  content: %s\n",g_minishell->args[i].content);
		printf("\t  type: %zu\n",g_minishell->args[i].type);
		i++;
	}*/

	return(1);
}