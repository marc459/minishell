SRCS	= get_next_line.c get_next_line_utils.c
OBJS	= ${SRCS:.c=.o}
NAME	= gnl.a
CC		= gcc
#CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

all: ${NAME}

$(NAME): ${OBJS}
	ar -crs ${NAME} ${OBJS}

clean:
	${RM} ${OBJS} ${OBJS_B}

fclean: clean
	${RM} ${NAME}

re: fclean all