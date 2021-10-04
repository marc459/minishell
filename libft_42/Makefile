NAME =  libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
ft_memcmp.c ft_strlen.c ft_strlcat.c ft_strlcpy.c ft_strchr.c \
ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
ft_isdigit.c ft_isalnum.c ft_isascii.c \
ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c \
ft_strjoin.c ft_substr.c ft_split.c ft_strtrim.c ft_itoa.c \
ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_strcmp.c ft_dectohex.c ft_hextodec.c ft_putstr.c ft_len.c \
ft_atol.c ft_bubblesort.c ft_bidstrlen.c ft_intarraydup.c ft_intcpy.c ft_putchar.c \
ft_itoa_without_minus.c ft_intlen.c ft_strrev.c ft_free_return.c ft_bintodec.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -I

OBJ = $(SRC:.c=.o)

BOBJ = $(BONUS:.c=.o)

all: $(NAME)
$(NAME):$(SRCS) libft.h
	@gcc -c $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

bonus:
	@gcc $(CFLAGS) -g -c $(BONUS) $(SRC)
	@ar rc $(NAME) $(BOBJ) $(OBJ)
	@ranlib $(NAME)
clean:
	@$(RM) $(OBJ)
	@$(RM) $(BOBJ)

fclean:     clean
	@$(RM) $(NAME)
re:     fclean all
