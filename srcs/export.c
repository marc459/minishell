/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:58:01 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/02 15:50:37 by marcos           ###   ########.fr       */
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
		if(lst->content)
			printf("%s=%s\n",lst->envvar, lst->content);
		else
			printf("%s\n",lst->envvar);
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

void swapenv(t_env *a, t_env *b)
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
                swapenv(ptr1,ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }

}

void	ft_checkenv(t_env *varenvs, t_env *new)
{
	int updated;
	updated = 0;
	t_env	*iter;

	iter = varenvs;
	while (iter)
	{
		
		if(!ft_strncmp(iter->envvar,new->envvar,ft_strlen(iter->envvar)))
		{
			iter->content = new->content;
			updated = 1;
		}
		iter = iter->next;
	}
	if(!updated)
		ft_envadd_back(&varenvs, new);
}

void	ft_parsebuiltin(t_general *g_mini,char **cmd)
{
	if(!ft_strncmp(cmd[0], "export", 7) && ft_bidstrlen(cmd) == 1)
	{
		printf("ENV VARS\n");
		ft_printenv(g_mini->varenvs);
	}
	else if(!ft_strncmp(cmd[0], "export", 7))
	{
		char *keyvar;
		char *valuevar;
		int i;
		int x;
		int y;

		i=1;
		keyvar = ft_calloc(ft_strlen(cmd[i]),sizeof(char));
		valuevar = ft_calloc(ft_strlen(cmd[i]),sizeof(char));
		while(cmd[i])
		{
			x = 0;
			y = 0;
			while(cmd[i][x] && cmd[i][x] != '=')
			{
				keyvar[x] = cmd[i][x];
				x++;
			}
			x++;
			if(!cmd[i][x])
				valuevar = NULL;
			while(cmd[i][x])
			{
				valuevar[y] = cmd[i][x];
				x++;
				y++;
			}
			ft_checkenv(g_mini->varenvs,ft_envnew(ft_strdup(keyvar), ft_strdup(valuevar)));
			free(keyvar);
			free(valuevar);
			i++;
		}
		
	}
}