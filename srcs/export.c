/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:58:01 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/24 18:53:24 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*ft_envnew(char	*envvar,char *content)
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

void	ft_printenv(t_env *lst)
{
	while (lst)
	{
		printf("%s=%s\n",lst->envvar, lst->content);
		lst = lst->next;
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

void swap2(t_env *a, t_env *b)
{
    char *temp = a->envvar;
    a->envvar = b->envvar;
    b->envvar = temp;

	/*t_env *bn = b->next;
	t_env *bb = b->back;
	t_env *an = a->next;
	t_env *ab = a->back;
    b->next = a;
	b->back = ab;
	a->next = bn;
	a->back = b;*/
}

void bubbleSort(t_env *start)
{
    int swapped, i;
    t_env *ptr1;
    t_env *lptr = NULL;
  
    if (start == NULL)
        return;
  
    while(swapped)
    {
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            if (ft_strncmp(ptr1->envvar, ptr1->next->envvar, ft_strlen(ptr1->envvar)) > 0)
            { 
                swap2(ptr1,ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }

}


