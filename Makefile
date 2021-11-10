#PROGRAMS
PROGRAM = minishell

#LIBS
LIBFT = libft_42/libft.a
PRINTF = ft_printf_42/libftprintf.a
READLINE = readline/libreadline.a
#readline/libhistory.a 
LIBS = $(LIBFT) $(PRINTF)

#PATHS
OBJ_PATH = ./objs
SRC_PATH = ./srcs
INCLUDES = -I ./includes -I ./readline -I ./readline/examples

#SRCS
PROGRAM_SRCS = minishell.c parser.c signals.c executor.c process.c

#OBJS
PROGRAM_OBJS = $(addprefix $(OBJ_PATH)/,$(PROGRAM_SRCS:.c=.o))
	
#FLAGS
CC = gcc
CFLAGS =  -g3 -fsanitize=address
# -Wall -Werror -Wextra

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
all: submodule ft_printf libft minishell
	
#EVERY TIME A .O IS CALLED AS AN INSTRUCTION THIS WILL BE CREATED IN OBJ_PATH
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(INCLUDES) -o $@ -c $^
			
submodule:
	@git submodule init
	@git submodule update --remote
					
#CHECKS THE EXISTANCE OF AN COMPILING FTPRINTF LIBRARY 
ft_printf:
	@make -C ft_printf_42  > /dev/null
libft:
	@make -C libft_42 > /dev/null
							
minishell: $(PROGRAM_OBJS)
	@$(CC) $(CFLAGS) $(PROGRAM_OBJS) $(LIBFT) $(PRINTF) $(READLINE) $(TERMCAP_LIB) -o $(PROGRAM)
								
clean:
	@rm -rf $(OBJ_PATH)
									
fclean: clean
	@rm -rf $(PROGRAM) $(CLIENT)
	@make fclean -C ft_printf_42 > /dev/null
	@make fclean -C libft_42 > /dev/null
												
re: fclean all
