/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:30:21 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:13:55 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastnode;

	if (new)
	{
		lastnode = ft_lstlast(lst[0]);
		if (*lst == NULL)
		{
			*lst = new;
			new->next = NULL;
		}
		else
		{
			lastnode->next = new;
			new->next = NULL;
		}
	}
}
