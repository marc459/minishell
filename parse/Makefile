# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 15:15:09 by emgarcia          #+#    #+#              #
#    Updated: 2021/11/08 16:56:37 by emgarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_args3.c ft_args2.c ft_args.c ft_aux2.c ft_aux.c ft_parse.c main.c
LIBFT	=	Libft/libft.a
OBJS	=	${SRCS:.c=.o}
NAME	=	parse
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3
#CFLAGS	=	-Wall -Wextra -Werror
RM	=	rm -rf

all: submodule ${NAME}

${NAME}: ${OBJS}
	@make -C Libft
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

submodule:
	@git submodule init
	@git submodule update --remote

clean:
	@cd Libft ; make fclean
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
