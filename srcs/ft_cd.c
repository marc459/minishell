/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:57:11 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/25 17:19:30 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_getpathpos(char	**env)
{
	size_t	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PWD", 3))
			return (i);
	return (0);
}

size_t	ft_getoldpathpos(char	**env)
{
	size_t	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "OLDPWD", 6))
			return (i);
	return (0);
}

void	ft_cd(char	***env, char *path)
{
	char	*pwdbuf;
	char	*auxpath;

	if (!chdir(path))
	{
		free (env[0][ft_getoldpathpos(env[0])]);
		auxpath = ft_strjoin("OLD", env[0][ft_getpathpos(env[0])]);
		env[0][ft_getoldpathpos(env[0])] = ft_strdup(auxpath);
		free (auxpath);
		pwdbuf = calloc(sizeof(char), (PATH_MAX + 1));
		getcwd(pwdbuf, PATH_MAX);
		free (env[0][ft_getpathpos(env[0])]);
		env[0][ft_getpathpos(env[0])] = ft_strjoin("PWD=", pwdbuf);
		free (pwdbuf);
	}
	else
		printf("cd: no such file or directory: %s\n", path);
}
