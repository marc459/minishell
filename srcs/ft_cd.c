/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:57:11 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/15 17:44:28 by msantos-         ###   ########.fr       */
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
		/*if (env[0][ft_getoldpathpos(env[0])])
			free (env[0][ft_getoldpathpos(env[0])]);*/
		auxpath = ft_strjoin("OLD", env[0][ft_getpathpos(env[0])]);
		env[0][ft_getoldpathpos(env[0])] = ft_strdup(auxpath);
		free (auxpath);
		pwdbuf = calloc(sizeof(char), (PATH_MAX + 1));
		getcwd(pwdbuf, PATH_MAX);
		/*if (env[0][ft_getpathpos(env[0])])
			free (env[0][ft_getpathpos(env[0])]);*/
		env[0][ft_getpathpos(env[0])] = ft_strjoin("PWD=", pwdbuf);
		free (pwdbuf);
	}
	else
	{
		
		/*ft_putstr_fd("minishell: cd: ",2);
		ft_putstr_fd(path,2);
		ft_putstr_fd(": No such file or directory\n",2);*/
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		g_piperet = 1;
	}
		
}
