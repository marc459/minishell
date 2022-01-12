/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 07:12:59 by emgarcia          #+#    #+#             */
/*   Updated: 2022/01/12 19:48:43 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_countkeyvalue(char *str, int quote, int dquote)
{
	size_t	i;
	size_t	last;
	size_t	size;

	if (!str)
		return (0);
	i = -1;
	size = 0;
	last = 0;
	while (str[++i])
	{
		if (str[i] == ' ' && dquote > 0 && quote > 0)
		{
			if (i - last > 0)
				size++;
			last = i;
		}
		if (str[i] == '\'' && dquote > 0)
			quote *= -1;
		if (str[i] == '\"' && quote > 0)
			dquote *= -1;
	}
	if (str[i - 1] != ' ')
		size++;
	return (size);
}

void	ft_changequote(int *quote, int *dquote, char c)
{
	if (c == '\'' && *dquote > 0)
		*quote *= -1;
	if (c == '\"' && *quote > 0)
		*dquote *= -1;
}

char	**ft_dropkeyvalue(char *str, int quote, int dquote)
{
	size_t	i;
	size_t	j;
	size_t	last;
	char	**cmd;

	cmd = ft_calloc(sizeof(char *), (ft_countkeyvalue(str, 1, 1) + 1));
	if (!cmd)
		return (NULL);
	i = -1;
	j = 0;
	last = 0;
	while (str[++i])
	{
		if (str[i] == ' ' && dquote > 0 && quote > 0)
		{
			if (i - last > 0)
				cmd[j++] = ft_substr(str, last, i - last);
			last = i + 1;
		}
		ft_changequote(&quote, &dquote, str[i]);
	}
	if (str[i - 1] != ' ')
		cmd[j++] = ft_substr(str, last, i - last);
	return (cmd);
}

char	**ft_splitkeyvalue(t_general *g, char *str)
{
	size_t	i;
	char	**cmd;
	char	*aux;

	if (!str)
		return (NULL);
	cmd = ft_dropkeyvalue(str, 1, 1);
	i = -1;
	while (cmd[++i])
	{
		if (ft_findchar(cmd[i], '\'') || ft_findchar(cmd[i], '\"'))
		{
			aux = ft_dropquotes(g, cmd[i]);
			free (cmd[i]);
			cmd[i] = ft_strdup(aux);
			free (aux);
		}
	}
	return (cmd);
}

int	ft_parsebuiltin(t_general *g, char **cmd, int i)
{
	if (!ft_strncmp(cmd[0], "export", 6) && ft_bidstrlen(cmd) > 1)
	{
		while (cmd[++i])
			ft_checknewenv(g, cmd[i]);
		return (1);
	}
	else if (!ft_strncmp(cmd[0], "export\0", 7) && ft_bidstrlen(cmd) == 1)
	{
		ft_printsortenv(g->ownenv);
		return (1);
	}
	else if (!ft_strncmp(cmd[0], "unset\0", 6))
	{
		while (cmd[++i])
			ft_remenv(g, cmd[i]);
		return (1);
	}
	else if (!ft_strncmp(cmd[0], "exit", 4))
		exit_error(cmd);
	if (!ft_strncmp(cmd[0], "cd", 2))
	{
		ft_cd(&g->ownenv, cmd[1]);
		return (1);
	}	
	return (0);
}
