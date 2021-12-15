# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 13:26:03 by emgarcia          #+#    #+#              #
#    Updated: 2021/12/15 17:42:29 by msantos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_PRINTF_SRCS_PATH = ./ft_printf

SRCS	=	ft_strtrim.c	\
			ft_putnbr_fd.c	\
			ft_putendl_fd.c	\
			ft_putstr_fd.c	\
			ft_putchar_fd.c	\
			ft_striteri.c	\
			ft_strmapi.c	\
			ft_itoa.c		\
			ft_strdup.c		\
			ft_calloc.c		\
			ft_atoi.c		\
			ft_memcmp.c		\
			ft_memchr.c		\
			ft_strncmp.c	\
			ft_strrchr.c	\
			ft_strchr.c		\
			ft_tolower.c	\
			ft_toupper.c	\
			ft_strlcat.c	\
			ft_strlcpy.c	\
			ft_memmove.c	\
			ft_memcpy.c		\
			ft_bzero.c		\
			ft_memset.c		\
			ft_isprint.c	\
			ft_isascii.c	\
			ft_isalnum.c	\
			ft_isdigit.c	\
			ft_substr.c		\
			ft_strlen.c		\
			ft_strjoin.c	\
			ft_strnstr.c	\
			ft_split.c		\
			ft_isalpha.c	\
			ft_atol.c		\
			ft_bidstrlen.c	\
			ft_bintodec.c	\
			ft_bubblesort.c	\
			ft_free_return.c	\
			ft_getnextline.c	\
			ft_hextodec.c	\
			ft_intarraydup.c	\
			ft_intcpy.c		\
			ft_intlen.c		\
			ft_itoa_without_minus.c	\
			ft_len.c \
			ft_freebidstr.c \
			ft_splitjoin.c	\
			ft_getposition.c	\
			ft_trimchar.c	\
			ft_revtrimchar.c	\
			ft_splitlen.c	\
			ft_trimallchar.c	\
			ft_countchar.c	\
			ft_strownjoin.c	\
			ft_strsort.c	\
			ft_splitdup.c	\
			ft_splitprint.c \
			ft_putchar.c \
			ft_strrev.c

FT_PRINTF_SRCS = flag_sorting.c ft_printf.c initialize_flags.c \
print_integer.c print_string.c variable_sorting.c ft_putstrcounter.c \
print_character.c print_hexadecimal.c print_ptr.c print_percentage.c \
print_unsigned.c print_charxtimes.c \
check_width.c check_precision.c check_zero.c

SRCS_B	= ft_lstmap.c ft_lstiter.c ft_lstclear.c ft_lstdelone.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstadd_front.c ft_lstnew.c
OBJS	= ${SRCS:.c=.o}
OBJS_B	= ${SRCS_B:.c=.o}
PRINTFOBJS = $(FT_PRINTF_SRCS:.c=.o)

GNLA	= get_next_line/gnl.a
NAME	= libft.a
CC		= gcc
#CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
FT_PRINTF_OBJS = $(addprefix $(FT_PRINTF_SRCS_PATH)/, $(PRINTFOBJS))

all: submodule ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

$(FT_PRINTF_SRCS_PATH)/%.o: $(FT_PRINTF_SRCS_PATH)/%.c
	@gcc -o $@ -c $<

$(NAME): ${OBJS} $(FT_PRINTF_OBJS)
	@make -C get_next_line
	@cp ${GNLA} ${NAME}
	@ar -crs ${NAME} ${OBJS} $(FT_PRINTF_OBJS)

submodule:
	@git submodule init
	@git submodule update --remote

bonus: ${OBJS_B} ${OBJS}
	@ar -crs ${NAME} ${OBJS_B} ${OBJS}

clean:
	@cd get_next_line ; make fclean
	@${RM} ${OBJS} ${OBJS_B}

fclean: clean
	@${RM} ${NAME}

re: fclean all
