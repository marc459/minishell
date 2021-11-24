/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 20:25:14 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/23 17:59:19 by msantos-         ###   ########.fr       */
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
