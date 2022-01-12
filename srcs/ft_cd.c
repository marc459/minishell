/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:57:11 by emgarcia          #+#    #+#             */
/*   Updated: 2022/01/12 17:31:27 by emgarcia         ###   ########.fr       */
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

int	ft_getenvpos(char *envvar, char **env)
{
	size_t	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], envvar, ft_strlen(envvar)))
			return (i);
	return (-1);
}

void	ft_changepwds(char ***env, char *auxoldpath, char *auxpath)
{
	char	**newenv;
	size_t	i;

	newenv = ft_calloc(sizeof(char *), (ft_splitlen(env[0]) + 1));
	i = -1;
	while (env[0][++i])
	{
		if (!ft_strncmp(env[0][i], "OLDPWD", 6))
			newenv[i] = auxoldpath;
		else if (!ft_strncmp(env[0][i], "PWD", 3))
			newenv[i] = auxpath;
		else
			newenv[i] = ft_strdup(env[0][i]);
	}
	ft_freedouble(env[0]);
	env[0] = newenv;
}

void	ft_cd(char	***env, char *path)
{
	char	*pwdbuf;
	char	*auxpath;
	char	*auxoldpath;

	if (!path && ft_getenvpos("HOME\0", env[0]) != -1)
	{
		auxpath = ft_substr(env[0][ft_getenvpos("HOME\0", env[0])], 5,
				ft_strlen(env[0][ft_getenvpos("HOME\0", env[0])]));
		chdir(auxpath);
		free (auxpath);
	}
	else if (chdir(path))
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return ;
	}
	auxoldpath = ft_strjoin("OLD", env[0][ft_getpathpos(env[0])]);
	pwdbuf = ft_calloc(sizeof(char), (PATH_MAX + 1));
	getcwd(pwdbuf, PATH_MAX);
	auxpath = ft_strjoin("PWD=", pwdbuf);
	free (pwdbuf);
	ft_changepwds(env, auxoldpath, auxpath);
}
