/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:22:15 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/25 15:33:45 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	main(int argc, char *split[])
{
	t_general	general;

	ft_inigeneral(&general);
	ft_parse(argc, split, &general);
	system("leaks parse");
	return (0);
}
