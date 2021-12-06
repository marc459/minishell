/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:18:15 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/06 18:48:35 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_checkenvname(char *name)
{
	size_t	i;

	i = -1;
	while (name[++i])
	{
		if (!i && !ft_isalpha(name[i]))
			return (0);
		else if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]))
			return (0);
	}
	return (1);
}

size_t	ft_modenv(t_general *g, char *name, char **gvar)
{
	size_t	i;

	i = -1;
	while (g->ownenv[++i])
	{
		if (ft_strncmp(name, g->ownenv[i], ft_strlen(name)) == 0
			&& (g->ownenv[i][ft_strlen(name)] == '='
			|| !g->ownenv[i][ft_strlen(name)]))
		{
			free (g->ownenv[i]);
			g->ownenv[i] = *gvar;
			return (1);
		}
	}
	return (0);
}

void	ft_addenv(t_general *g, char *name, char *val)
{
	size_t	i;
	char	*gvar;
	char	**newenv;

	gvar = ft_strdup(name);
	if (ft_strlen(val))
	{
		ft_strownjoin(&gvar, "=\"");
		ft_strownjoin(&gvar, val);
		ft_strownjoin(&gvar, "\"");
	}
	if (ft_modenv(g, name, &gvar))
		return ;
	newenv = calloc(sizeof(char *), (ft_splitlen(g->ownenv) + 2));
	if (!newenv)
		return ;
	i = -1;
	while (g->ownenv[++i])
		newenv[i] = ft_strdup(g->ownenv[i]);
	newenv[i] = gvar;
	ft_freedouble(g->ownenv);
	g->ownenv = newenv;
}

void	ft_checknewenv(t_general *g, char *newenv)
{
	size_t	i;
	size_t	ultima;
	char	*name;
	char	*val;

	i = 0;
	ultima = 0;
	while (newenv[i] && newenv[i] != '=')
		i++;
	name = ft_substr(newenv, ultima, i);
	ultima = i + 1;
	if (!ft_checkenvname(name))
		return ;
	val = ft_substr(newenv, ultima, i - ultima);
	ultima = i + 1;
	ft_addenv(g, name, val);
	free (name);
	free (val);
}
