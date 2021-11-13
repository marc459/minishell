/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 18:15:52 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/08 16:13:15 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*primero;
	t_list	*aux;
	t_list	*nuevo;

	if (!lst)
		return (NULL);
	aux = lst;
	primero = ft_lstnew(f (aux->content));
	aux = aux->next;
	while (aux)
	{
		nuevo = ft_lstnew(f (aux->content));
		if (!nuevo)
		{
			ft_lstclear(&primero, del);
			return (NULL);
		}
		ft_lstadd_back(&primero, nuevo);
		aux = aux->next;
	}
	return (primero);
}
