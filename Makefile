#PROGRAMS
PROGRAM = minishell
UNAME_S := $(shell uname -s)

#LIBS
LIBFT = libft.a
READLINE = readline/libreadline.a readline/libhistory.a 


#PATHS
OBJ_PATH = ./objs
SRC_PATH = ./srcs
LIBFT_PATH = ./libft
INCLUDES = -I ./includes -I ./readline -I ./readline/examples
LIBS = $(LIBFT_PATH)/$(LIBFT) $(READLINE)

#SRCS
PROGRAM_SRCS = minishell.c signals.c executor.c executor2.c executor3.c		\
				parse/ft_args.c parse/ft_args2.c parse/ft_args3.c	\
				parse/ft_aux.c parse/ft_aux2.c parse/ft_parse.c	\
				 parse/ft_args4.c ft_cd.c ft_ownenv.c	\
				parse/ft_aux3.c ft_addenv.c ft_remenv.c	\
				ft_expuns.c heredock.c parse/ft_dropquotes.c	\
				ft_splitaux.c utils.c utils2.c ft_echo.c

#OBJS
PROGRAM_OBJS = $(addprefix $(OBJ_PATH)/,$(PROGRAM_SRCS:.c=.o))
	
#FLAGS
CC = gcc
CFLAGS =  -Wall -Werror -Wextra

# SANITIZE ADDRESS
ifeq ($(UNAME_S),Linux)
	CFLAGS += -pedantic -g3 -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -pedantic -g3 -fsanitize=address
endif

ifeq ($(OS),Windows_NT) 
 detected_OS := Windows
else
 detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Darwin)
 TERMCAP_LIB = -ltermcap
endif
ifeq ($(detected_OS),Linux)
 TERMCAP_LIB =
endif

#INSTRUCTIONS
all: libftt minishell
	
#EVERY TIME A .O IS CALLED AS AN INSTRUCTION THIS WILL BE CREATED IN OBJ_PATH
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)/parse 2> /dev/null || true
	@$(CC) $(INCLUDES) -o $@ -c $^
			
submodule:
	@git submodule init
	@git submodule update --remote

libftt:
	@make -C $(LIBFT_PATH)
							
minishell: $(PROGRAM_OBJS)
	
	$(CC) $(CFLAGS) $(PROGRAM_OBJS)  $(LIBS) $(TERMCAP_LIB) -o $(PROGRAM)
								
clean:
	@rm -rf $(OBJ_PATH)
									
fclean: clean
	@rm -rf $(PROGRAM)
	@make fclean -C $(LIBFT_PATH) > /dev/null
												
re: fclean all
