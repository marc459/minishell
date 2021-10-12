/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:26:09 by msantos-          #+#    #+#             */
/*   Updated: 2021/10/12 20:16:16 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Divides command line in (command,file,pipe,expansion)
int		parser(char *command)
{
	char	**commands;
	int i;

	i = 0;
	commands = ft_split(command,' ');
	while(commands[i])
	{
		ft_printf("%s\n",commands[i]);
		i++;
	}
	return(1);
}