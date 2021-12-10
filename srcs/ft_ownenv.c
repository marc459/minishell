/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ownenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:59:22 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/10 18:18:55 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_printsortenv(char **ownenv)
{
	size_t	i;
	char	**sort;

	if (!ownenv)
		return ;
	sort = ft_strsort(ownenv);
	i = -1;
	while (sort[++i])
		printf("declare -x %s\n", sort[i]);
	ft_freedouble(sort);
}

void	ft_makeenv(char ***ownenv)
{
	char	*pwdbuf;

	pwdbuf = calloc(sizeof(char), (PATH_MAX + 1));
	getcwd(pwdbuf, PATH_MAX);
	ownenv[0][0] = ft_strjoin("PWD=", pwdbuf);
	ownenv[0][1] = ft_strjoin("OLDPWD=", pwdbuf);
	ownenv[0][2] = ft_strdup("SHLVL=2");
	ownenv[0][3] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin");
	ft_strownjoin(&ownenv[0][3], ":/sbin:/usr/local/munki");
	free (pwdbuf);
}

char	**ft_ownenv(char **environ)
{
	char	**ownenv;
	size_t	i;

	if (ft_splitlen(environ))
	{
		ownenv = calloc(sizeof(char *), (ft_splitlen(environ) + 1));
		if (!ownenv)
			return (NULL);
		i = -1;
		while (++i < ft_splitlen(environ))
			ownenv[i] = ft_strdup(environ[i]);
	}
	else
	{
		ownenv = calloc(sizeof(char *), 5);
		if (!ownenv)
			return (NULL);
		ft_makeenv(&ownenv);
	}
	return (ownenv);
}
