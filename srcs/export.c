/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:58:01 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/05 07:13:28 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*ft_envnew(char	*envvar, char *content)
{
	t_env	*el_list;

	el_list = (t_env *)malloc(sizeof(t_env));
	if (el_list == NULL)
		return (NULL);
	el_list->content = content;
	el_list->envvar = envvar;
	el_list->next = NULL;
	el_list->back = NULL;
	return (el_list);
}

t_env	*ft_envlast(t_env *lst)
{
	t_env	*returned;

	returned = lst;
	while (returned)
	{
		if (!returned->next)
			return (returned);
		returned = returned->next;
	}
	return (returned);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*check;

	if (lst)
	{
		if (*lst)
		{
			check = ft_envlast(*lst);
			check->next = new;
			new->back = check;
		}
		else
			*lst = new;
	}
}

int	ft_envsize(t_env *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	swapenv(t_env *a, t_env *b)
{
	char	*temp;

	temp = a->envvar;
	a->envvar = b->envvar;
	b->envvar = temp;
}

void	bubbleSort(t_env *start)
{
	int		swapped;
	int		i;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	if (start == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->envvar, ptr1->next->envvar, ft_strlen(ptr1->envvar)) > 0)
			{
				swapenv(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
void	ft_envadd_front(t_env **lst, t_env *new)
{
	new->next = lst[0];
	lst[0] = new;
}

void	ft_checkenv(t_env **varenvs, char *keyvar, char *valuevar)
{
	int		updated;
	int		placed;
	t_env	*iter;
	t_env	*new;

	updated = 0;
	iter = *varenvs;
	while (iter)
	{
		if (!ft_strncmp(iter->envvar, keyvar, ft_strlen(iter->envvar) + 1))
		{
			iter->content = valuevar;
			updated = 1;
		}
		iter = iter->next;
	}
	iter = *varenvs;
	if (!updated)
	{
		new = ft_envnew(ft_strdup(keyvar), ft_strdup(valuevar));
		placed = 0;
		if (ft_strncmp(iter->envvar, keyvar, ft_strlen(keyvar) + 1) > 0)
			ft_envadd_front(varenvs, new);
		while (iter && !placed)
		{
			if (ft_strncmp(iter->envvar, keyvar, ft_strlen(keyvar) + 1) > 0)
			{
				placed = 1;
				if (iter->back != NULL)
				{
					iter->back->next = new;
					new->back = iter->back;
					iter->back = new;
				}
				else
					new->back = NULL;
				new->next = iter;
				break ;
			}
			iter = iter->next;
		}
		if (!placed)
			ft_envadd_back(varenvs, new);
	}		
}

void	ft_deleteenv(t_env **varenvs, char *keyvar)
{
	t_env	*iter;

	iter = *varenvs;
	while (iter)
	{
		if (!ft_strncmp(iter->envvar, keyvar, ft_strlen(iter->envvar) + 1))
		{
			if (iter->back)
				iter->back->next = iter->next;
			else
				*varenvs = varenvs[0]->next;
		}
		iter = iter->next;
	}
}
