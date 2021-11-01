# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcos <marcos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 15:15:09 by emgarcia          #+#    #+#              #
#    Updated: 2021/11/01 13:53:06 by marcos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_args.c ft_aux2.c ft_aux.c ft_parse.c main.c
LIBFT	=	libft/libft.a
OBJS	=	${SRCS:.c=.o}
NAME	=	parse
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3
#CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

all:	${NAME}

${NAME}: ${OBJS}
	@make -C libft
	${CC} ${CFLAGS} ${LIBFT} ${OBJS} -o ${NAME}

clean:
	@cd libft ; make fclean
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all