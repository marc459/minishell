/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strownjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:40:05 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/30 13:49:37 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strownjoin(char **s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*final;

	if (!s1[0] && !s2)
		;
	i = -1;
	j = -1;
	final = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (final == NULL)
		;
	if (!s1[0])
		i = 0;
	while (s1[0] && s1[0][++i] != '\0')
		final[i] = s1[0][i];
	if (!s2)
		j = 0;
	while (s2 && s2[++j] != '\0')
		final[i + j] = s2[j];
	final[i + j] = '\0';
	if (s1[0])
		free (s1[0]);
	s1[0] = final;
}
