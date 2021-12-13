/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 07:12:59 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/13 16:13:46 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_countkeyvalue(char *str)
{
	size_t	i;
	size_t	size;
	int		quote;
	int		dquote;

	if (!str)
		return (0);
	i = -1;
	quote = 1;
	dquote = 1;
	size = 0;
	while (str[++i])
	{
		if (str[i] == ' ' && dquote > 0 && quote > 0)
			size++;
		if (str[i] == '\'' && dquote > 0)
			quote *= -1;
		if (str[i] == '\"' && quote > 0)
			dquote *= -1;
	}
	if (str[i - 1] != ' ')
		size++;
	return (size);
}

char	**ft_dropkeyvalue(char *str, size_t size, int quote, int dquote)
{
	size_t	i;
	size_t	j;
	size_t	ultima;
	char	**cmd;

	cmd = ft_calloc(sizeof(char *), (size + 1));
	if (!cmd)
		return (NULL);
	i = -1;
	j = 0;
	ultima = 0;
	while (str[++i])
	{
		if (str[i] == ' ' && dquote > 0 && quote > 0)
		{
			cmd[j++] = ft_substr(str, ultima, i - ultima);
			ultima = i + 1;
		}
		if (str[i] == '\'' && dquote > 0)
			quote *= -1;
		if (str[i] == '\"' && quote > 0)
			dquote *= -1;
	}
	if (str[i - 1] != ' ')
		cmd[j++] = ft_substr(str, ultima, i - ultima);
	return (cmd);
}

char	**ft_splitkeyvalue(t_general *g, char *str)
{
	size_t	size;
	size_t	i;
	char	**cmd;
	char	*aux;

	if (!str)
		return (NULL);
	size = ft_countkeyvalue(str);
	cmd = ft_dropkeyvalue(str, size, 1, 1);
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

void	ft_parsebuiltin(t_general *g, char **cmd)
{
	int		i;
	char	*joined;
	char	**auxcmd;

	i = 0;
	if (!ft_strncmp(cmd[0], "export", 7) && ft_bidstrlen(cmd) == 1)
		ft_printsortenv(g->ownenv);
	else if (!ft_strncmp(cmd[0], "export", 6))
	{
		joined = ft_splitjoin(&cmd[1], ' ');
		auxcmd = ft_splitkeyvalue(g, joined);
		free (joined);
		i = -1;
		while (auxcmd[++i])
			ft_checknewenv(g, auxcmd[i]);
		free(auxcmd);
	}
	else if (!ft_strncmp(cmd[0], "unset", 5))
		while (cmd[++i])
			ft_remenv(g, cmd[i]);
}
