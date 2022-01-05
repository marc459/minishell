/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:57:11 by emgarcia          #+#    #+#             */
/*   Updated: 2022/01/05 22:15:40 by marcos           ###   ########.fr       */
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

size_t	ft_getenvpos(char *envvar, char **env)
{
	size_t	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], envvar, ft_strlen(envvar)))
			return (i);
	return (0);
}

void	ft_cd(t_general *g, char *path)
{
	char	*pwdbuf;
	char	*auxpath;

	if (!path)
	{
		auxpath = ft_substr(g->ownenv[ft_getenvpos("HOME", g->ownenv)], 5,
				ft_strlen(g->ownenv[ft_getenvpos("HOME", g->ownenv)]));
		chdir(auxpath);
		free (auxpath);
	}
	else if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		commandoutput(1);
		return ;
	}
	else{
		if(!ft_getoldpathpos(g->ownenv))
		{
			printf("no existe OLDPATH\n");
			ft_addenv(g, "OLDPWD", g->ownenv[ft_getpathpos(g->ownenv)] + 5);
		}
		else{
			auxpath = ft_strjoin("OLDPWD=", g->ownenv[ft_getpathpos(g->ownenv)] + 4);
			free (g->ownenv[ft_getoldpathpos(g->ownenv)]);
			g->ownenv[ft_getoldpathpos(g->ownenv)] = auxpath;
		}
		pwdbuf = ft_calloc(sizeof(char), (PATH_MAX + 1));
		getcwd(pwdbuf, PATH_MAX);
		printf("getpathpos:%ld, %ld\n", ft_getpathpos(g->ownenv),ft_getoldpathpos(g->ownenv));
		free (g->ownenv[ft_getpathpos(g->ownenv)]);
		g->ownenv[ft_getpathpos(g->ownenv)] = ft_strjoin("PWD=", pwdbuf);
		free (pwdbuf);
	}
}
