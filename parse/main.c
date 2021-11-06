/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:22:15 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/05 21:39:16 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	main(int argc, char *split[])
{
	t_general	general;
	size_t		i;
	char		*join;
	char		*aux;

	atexit(leak);
	i = 0;
	join = ft_strdup(split[i]);
	while (++i < (size_t)argc)
	{
		aux = join;
		join = ft_strjoin(join, " ");
		free(aux);
		aux = join;
		join = ft_strjoin(join, split[i]);
		free(aux);
	}
	printf("join : %s\n", join);
	ft_inigeneral(&general);
	ft_printgeneral(&general);
	printf("\n");
	ft_parse(&general, join);
	ft_printgeneral(&general);
	free (join);
	ft_freeall(&general);
	return (0);
}
