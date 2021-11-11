# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcos <marcos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 15:15:09 by emgarcia          #+#    #+#              #
#    Updated: 2021/11/11 14:08:55 by marcos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_args3.c ft_args2.c ft_args.c ft_aux2.c ft_aux.c ft_parse.c main.c
OBJS	=	${SRCS:.c=.o}
NAME	=	parse
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3
#CFLAGS	=	-Wall -Wextra -Werror
RM	=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

clean:
	@cd Libft ; make fclean
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
