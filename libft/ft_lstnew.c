/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 19:30:54 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/07 21:04:28 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*el_list;

	el_list = (t_list *)malloc(sizeof(t_list));
	if (el_list == NULL)
		return (NULL);
	el_list->content = content;
	el_list->next = NULL;
	return (el_list);
}
