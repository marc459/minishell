/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:29:50 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/15 17:42:19 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "get_next_line/get_next_line.h"
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*here list all used functions*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

long	ft_atol(const char *str);
int		ft_bidstrlen(char **arr);
int		ft_bintodec(long long n);
int		*ft_bubble_sort(int *messy_nums, int length);
int		ft_free_return(void *str, int ret);
int		get_next_line_p(char **line);
int		ft_hextodec(char *hexval);
int		*ft_intarraydup(int *n1);
void	*ft_intcpy(int *dst, int *src, size_t n);
int		ft_intlen(const long int value);
char	*ft_itoa_without_minus(long int n);
int		ft_len(long nb);
void	ft_freebidstr(char **s);
char	*ft_splitjoin(char	**split, char cjoin);
size_t	ft_getposition(char	*str, char c);
void	ft_trimchar(char **str, char c);
void	ft_revtrimchar(char **str, char c);
size_t	ft_splitlen(char **split);
void	ft_trimallchar(char **str, char c);
size_t	ft_countchar(char *str, char c);
void	ft_strownjoin(char **s1, char *s2);
char	**ft_splitdup(char **split);
char	**ft_strsort(char **split);
void	ft_splitprint(char **split);
void	ft_printsortenv(char **ownenv);
void	ft_putchar(char c);
char	*ft_strrev(char *str);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif