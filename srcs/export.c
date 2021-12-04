/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:58:01 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/04 18:28:10 by emgarcia         ###   ########.fr       */
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

void	ft_printenv(t_env *lst)
{
	while (lst)
	{
		if (lst->content)
			printf("declare -x %s=\"%s\"\n", lst->envvar, lst->content);
		else
			printf("declare -x %s\n", lst->envvar);
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

void	swapenv(t_env *a, t_env *b)
{
	char	*temp;

	temp = a->envvar;
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

void	ft_parsebuiltin(t_general *g_mini,char **cmd, char **envp)
{
	int		i;
	char	*keyvar;
	char	*valuevar;
	int		x;
	int		y;

	if (!ft_strncmp(cmd[0], "env", 4))
	{
		i = -1;
		while (++i < ft_bidstrlen(envp))
			printf("%s\n", envp[i]);
	}
	else if (!ft_strncmp(cmd[0], "export", 7) && ft_bidstrlen(cmd) == 1)
		ft_printenv(g_mini->varenvs);
	else if (!ft_strncmp(cmd[0], "export", 6))
	{
		i = 1;
		while (cmd[i])
		{
			x = 0;
			y = 0;
			while (cmd[i][x] && cmd[i][x] != '=')
				x++;
			keyvar = ft_substr(cmd[i], 0, x);
			if (cmd[i][x++] == '=')
				valuevar = ft_strdup(cmd[i] + x);
			else
			{
				valuevar = ft_strdup(cmd[i] + x);
				valuevar = NULL;
				printf("valuevar%s;\n", valuevar);
			}
			/*valuevar = ft_calloc(ft_strlen(cmd[i] + x),sizeof(char));
			printf(":%s:%ld\n",valuevar,ft_strlen(cmd[i] + x));*/
			/*if(cmd[i][x] == '\0')
			{
				printf("nocontent>%c;\n",cmd[i][x]);
				valuevar=NULL;
			}
			else{
				valuevar = ft_strdup(cmd[i] + x);
			}*/
			ft_checkenv(&g_mini->varenvs, keyvar, valuevar);
			free(keyvar);
			free(valuevar);
			i++;
		}
		//bubbleSort(g_mini->varenvs);
	}
	else if (!ft_strncmp(cmd[0], "unset", 5))
	{
		i = 1;
		while (cmd[i])
			ft_deleteenv(&g_mini->varenvs, cmd[i++]);
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
