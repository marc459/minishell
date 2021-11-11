/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:26:09 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/10 22:17:37 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Divides command line in (command,file,pipe,expansion)
char **provisional_parser(t_general *g_minishell,char *command)
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
		if(command[i] == '>')
			g_minishell->nredirections += 2;
		if(command[i] == '<')
			g_minishell->nredirections += 2;
		i++;
	}
	i = 0;
	g_minishell->ncomands = g_minishell->npipes + 1;
	g_minishell->args = malloc(sizeof(t_arg) * (g_minishell->ncomands + g_minishell->npipes + g_minishell->nredirections));
	printf("nargs%ld\n",g_minishell->ncomands + g_minishell->npipes + g_minishell->nredirections);
	while(pos < g_minishell->ncomands + g_minishell->npipes + g_minishell->nredirections)
	{
		while(comands[pos][y])
		{
			if(comands[pos][y] == '_')
				comands[pos][y] = ' ';
			y++;
		}
		g_minishell->args[pos].content = comands[pos];
		//g_minishell->args[pos].type = 3;
		pos++;
		if(x < g_minishell->nredirections)
		{
			g_minishell->args[pos].content = comands[pos];
			//g_minishell->args[pos].type = 1;
			x++;
			pos++;
		}
		i++;	
	}
	g_minishell->args[0].type = 1;
	g_minishell->args[1].type = 4;
	g_minishell->args[2].type = 3;

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
	//ft_freebidstr(comands);
	

	return(comands);
}