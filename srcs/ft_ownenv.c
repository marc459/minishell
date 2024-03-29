/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ownenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:59:22 by emgarcia          #+#    #+#             */
/*   Updated: 2022/01/13 19:10:25 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_printformat(char *sort)
{
	size_t	i;
	char	**split;

	split = ft_split(sort, '=');
	i = -1;
	while (split[++i])
	{
		if (!i)
			printf("declare -x %s", split[i]);
		if (i == 1)
			printf("=\"%s", split[i]);
		if (i > 1)
			printf("=%s", split[i]);
	}
	if (i == 1)
		printf("\n");
	else
		printf("\"\n");
	ft_freedouble(split);
}

int	ft_printsortenv(char **ownenv)
{
	size_t	i;
	char	**sort;

	if (!ownenv)
		return (1);
	sort = ft_strsort(ownenv);
	i = -1;
	while (sort[++i])
		ft_printformat(sort[i]);
	ft_freedouble(sort);
	return (1);
}

void	ft_makeenv(char ***ownenv)
{
	char	*pwdbuf;

	pwdbuf = ft_calloc(sizeof(char), (PATH_MAX + 1));
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
		ownenv = ft_calloc(sizeof(char *), (ft_splitlen(environ) + 1));
		if (!ownenv)
			return (NULL);
		i = -1;
		while (++i < ft_splitlen(environ))
			ownenv[i] = ft_strdup(environ[i]);
	}
	else
	{
		ownenv = ft_calloc(sizeof(char *), 5);
		if (!ownenv)
			return (NULL);
		ft_makeenv(&ownenv);
	}
	return (ownenv);
}
