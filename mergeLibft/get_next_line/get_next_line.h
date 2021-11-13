/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:14:11 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/27 13:59:12 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
void	ft_bzerognl(void *s);
char	*ft_dropchar(char *str);
size_t	ft_strlen(const char *s);
size_t	ft_findchar(char *str, char c);
size_t	ft_countcut(char *str);
char	*ft_cutstr(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_cutapend(int fd, ssize_t val, char *buf, char *line);

#endif
