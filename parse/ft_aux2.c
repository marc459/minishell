/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:11:14 by emgarcia          #+#    #+#             */
/*   Updated: 2021/10/28 04:27:36 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_freeall(t_general *g)
{
	size_t	i;

	i = -1;
	while (++i < g->parse.comndssize)
		free(g->parse.comnds[i]);
	free(g->parse.comnds);
	i = -1;
	while (++i < g->parse.comndssize)
		free(g->args[i].content);
	free(g->args);
}
