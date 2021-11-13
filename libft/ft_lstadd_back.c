/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 20:25:14 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/07 18:55:30 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*check;

	if (lst)
	{
		if (*lst)
		{
			check = ft_lstlast(*lst);
			check->next = new;
		}
		else
			*lst = new;
	}
}
