/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:58:01 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/23 23:07:17 by msantos-         ###   ########.fr       */
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
	char *firstenvar;
	int i;

	firstenvar = lst[0]->envvar;
	*lst = lst[0]->next;
	while (*lst)
	{
		if(ft_strncmp(firstenvar, lst[0]->envvar, ft_strlen(firstenvar)) > 0) //firstenvar goes first
		{
			printf("move to first position\n");
			lst[0]->envvar ==
			break ;
		}
		*lst = lst[0]->next;
	}
}


