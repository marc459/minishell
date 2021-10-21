# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 13:26:03 by emgarcia          #+#    #+#              #
#    Updated: 2021/09/13 18:58:16 by emgarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS	= get_next_line.c get_next_line_utils.c ft_strtrim.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_strdup.c ft_calloc.c ft_atoi.c ft_memcmp.c ft_memchr.c ft_strncmp.c ft_strrchr.c ft_strchr.c ft_tolower.c ft_toupper.c ft_strlcat.c ft_strlcpy.c ft_memmove.c ft_memcpy.c ft_bzero.c ft_memset.c ft_isprint.c ft_isascii.c ft_isalnum.c ft_isdigit.c ft_substr.c ft_strlen.c ft_strjoin.c ft_strnstr.c ft_split.c ft_isalpha.c
SRCS_B	= ft_lstmap.c ft_lstiter.c ft_lstclear.c ft_lstdelone.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstadd_front.c ft_lstnew.c
OBJS	= ${SRCS:.c=.o}
OBJS_B	= ${SRCS_B:.c=.o}
NAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
	@ar -crs ${NAME} ${OBJS}

bonus: ${OBJS_B} ${OBJS}
	ar -crs ${NAME} ${OBJS_B} ${OBJS}

clean:
	@${RM} ${OBJS} ${OBJS_B}

fclean: clean
	@${RM} ${NAME}

re: fclean all
