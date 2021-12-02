/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:58:01 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/02 21:36:29 by marcos           ###   ########.fr       */
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
        return ;
  
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

void	ft_checkenv(t_env *varenvs, char *keyvar, char *valuevar)
{
	int updated;
	int placed;
	updated = 0;
	t_env	*iter;

	iter = varenvs;
	
	while (iter)
	{
		if(!ft_strncmp(iter->envvar,keyvar,ft_strlen(iter->envvar) + 1))
		{
			iter->content = valuevar;
			updated = 1;
		}
		iter = iter->next;
	}
	iter = varenvs;
	if(!updated)
	{
		t_env *new = ft_envnew(ft_strdup(keyvar), ft_strdup(valuevar));
		placed = 0;
		while (iter && !placed)
		{
			//printf("iter->envvar: %s\n",iter->envvar);
			if (ft_strncmp(iter->envvar, keyvar, ft_strlen(keyvar) + 1) > 0)
            {
				placed = 1;
				/*t_env *tmp = iter->next;
				iter->next = new;
				new->next = tmp;*/

				/*t_env *tmp = iter;
				if(tmp->back)
					tmp->back->next = new;
				new->next = tmp;*/
				printf("iter->envvar%s,%sn",iter->envvar, keyvar);
				
				iter->back->next = new;
				printf("SF\n");
				if(iter->back)
					new->back = iter->back;
				else
					new->back=NULL;
				iter->back = new;
				new->next = iter;	
            }
			iter = iter->next;
		}
		//ft_envadd_back(&varenvs, new);
	}
		
}

void	ft_parsebuiltin(t_general *g_mini,char **cmd)
{
	if(!ft_strncmp(cmd[0], "export", 7) && ft_bidstrlen(cmd) == 1)
	{
		ft_printenv(g_mini->varenvs);
	}
	else if(!ft_strncmp(cmd[0], "export", 6))
	{
		char *keyvar;
		char *valuevar;
		int i;
		int x;
		int y;

		i=1;
		
		while(cmd[i])
		{
			keyvar = ft_calloc(ft_strlen(cmd[i]),sizeof(char));
			valuevar = ft_calloc(ft_strlen(cmd[i]),sizeof(char));
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
			ft_checkenv(g_mini->varenvs,keyvar, valuevar);
			free(keyvar);
			free(valuevar);
			
			i++;
		}
		//bubbleSort(g_mini->varenvs);
		
	}
}