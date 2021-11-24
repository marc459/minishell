/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:58:01 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/24 14:14:26 by msantos-         ###   ########.fr       */
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
void	ft_orderenv(t_env **lst)
{
	/*t_env *firstenvar;
	t_env *beforeenvar;
	int i;

	firstenvar = lst[0];
	beforeenvar = lst[0];
	*lst = lst[0]->next;
	while (*lst)
	{
		if(ft_strncmp(firstenvar->envvar, lst[0]->envvar, ft_strlen(firstenvar)) > 0) //lst[0]->envvar goes first
		{
			printf("move to first position\n");
			//lst[0] = firstenvar->envvar;
			break ;
		}
		*lst = lst[0]->next;
	}*/
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


void swap(t_env **node)
{
    t_env	*tmp;

	if (!(ft_envsize(*node) < 2))
	{
		tmp = *node;
		*node = (*node)->next;
		tmp->next = (*node)->next;
		(*node)->next = tmp;
	}
}

void swap2(t_env *a, t_env *b)
{
    char *temp = a->envvar;
    a->envvar = b->envvar;
    b->envvar = temp;

	//t_env *temp = a->next;
    //b->next = a;
	//a->next = b->next;
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


