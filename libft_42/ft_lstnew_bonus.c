/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:29:24 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:14:56 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list	*elemento;

	elemento = (t_list *)malloc(sizeof(t_list));
	if (elemento == NULL)
		return (NULL);
	if (content == NULL)
		elemento->content = NULL;
	else
	{
		elemento->content = (void *)content;
		elemento->next = NULL;
	}
	return (elemento);
}
