/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:58:01 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/23 18:00:40 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*ft_envnew(void *content)
{
	t_env	*el_list;

	el_list = (t_env *)malloc(sizeof(t_env));
	if (el_list == NULL)
		return (NULL);
	el_list->content = content;
	el_list->next = NULL;
	return (el_list);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*check;

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

