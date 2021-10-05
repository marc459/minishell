CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

LIB = ../libft_42/libft.a
LIB_PATH = ../libft_42/

SRC_PATH = ./src
INC_PATH = ./src
OBJ_PATH = ./objs

SRC_NAME = flag_sorting.c ft_printf.c initialize_flags.c \
print_integer.c print_string.c variable_sorting.c ft_putstrcounter.c \
print_character.c print_hexadecimal.c print_ptr.c print_percentage.c \
print_unsigned.c print_charxtimes.c \
check_width.c check_precision.c check_zero.c

INCLUDES = -I printf.h

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: libft $(NAME)

libft:
	@make -C ../libft_42  > /dev/null
	@if [ ! -f $(LIB) ]; then \
		echo Error, no existe la libreria $(LIB) ; \
	fi

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ) $(LIB_PATH)*.o
	@ranlib $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -o $@ -c $<

clean:
	@rm -rf $(OBJ) $(OBJLIB)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJ_PATH)

re: fclean all

.PHONY: fclean clean re
