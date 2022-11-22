# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 08:46:02 by rlins             #+#    #+#              #
#    Updated: 2022/11/22 07:16:15 by rlins            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Collors
RESET 	= \033[0m
GREEN 	= \033[0;32m
RED 	= \033[0;31m

# Paths
PATH_SRC 		= ./src/
PATH_MAIN 		= $(PATH_SRC)main/
PATH_INIT 		= $(PATH_SRC)init/
PATH_UTIL 		= $(PATH_SRC)util/
PATH_ENV 		= $(PATH_SRC)env/
PATH_BUILTINS 	= $(PATH_SRC)builtins/
PATH_LEXER		= $(PATH_SRC)lexer/
PATH_PARSER		= $(PATH_SRC)parser/
PATH_OBJS 		= ./objs/

INC_PATH 		= ./include/

# Libft files and directories
LIBFT_PATH 		= ./lib/libft/
LIBFT 			= ./lib/libft.a

# Compilation
CC = gcc

# TODO: RollBack this flags
# CFLAGS = -g -Wall -Werror -Wextra
CFLAGS = -g

#Chedk Leak memory
LEAK = valgrind --leak-check=full --show-leak-kinds=all \
	--trace-children=yes --suppressions=readline.supp --track-origins=yes -s

RM				= rm -rf
NO_PRINT	= --no-print-directory
READ_LN		= -l readline

INCLUDE = -I $(INC_PATH) -I $(LIBFT_PATH)

SRCS =	$(PATH_MAIN)main.c \
		$(PATH_INIT)init.c \
<<<<<<< HEAD
		$(PATH_INIT)init_cmds.c \
=======
		$(PATH_INIT)prompt.c \
>>>>>>> main
		$(PATH_INIT)init_structure.c \
		$(PATH_UTIL)exit.c \
		$(PATH_UTIL)signal.c \
		$(PATH_UTIL)sanitization.c \
		$(PATH_UTIL)split_args.c \
		$(PATH_ENV)env.c \
		$(PATH_ENV)env_partial.c \
		$(PATH_BUILTINS)builtins_handler.c \
		$(PATH_BUILTINS)cmd_exit.c \
		$(PATH_BUILTINS)cmd_pwd.c \
		$(PATH_BUILTINS)cmd_cd.c \
		$(PATH_BUILTINS)cmd_env.c \
		$(PATH_BUILTINS)cmd_export.c \
		$(PATH_BUILTINS)cmd_unset.c \
		$(PATH_BUILTINS)cmd_echo.c \
		$(PATH_LEXER)lexer.c \
		$(PATH_LEXER)complete_lexer.c \
		$(PATH_PARSER)parser.c

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRCS))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCLUDE) $(LIBFT) $(READ_LN)
	@echo "$(GREEN)Build Successful$(RESET)"

$(PATH_OBJS)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)main/
	@mkdir -p $(PATH_OBJS)init/
	@mkdir -p $(PATH_OBJS)util/
	@mkdir -p $(PATH_OBJS)env/
	@mkdir -p $(PATH_OBJS)builtins/
	@mkdir -p $(PATH_OBJS)lexer/
	@mkdir -p $(PATH_OBJS)parser/
	@$(CC) $(CFLAGS) $(INCLUDE) -I. -c $< -o $@

# Libft rule
$(LIBFT):
	@make -C $(LIBFT_PATH) $(NO_PRINT)

clean:
	@echo "$(RED)Cleaning objects...$(RESET)"
	@$(RM) $(PATH_OBJS)
	@make -C $(LIBFT_PATH) clean $(NO_PRINT)
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo  "$(RED)Cleaning all...$(RESET)"
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean $(NO_PRINT)
	@echo "$(RED)Cleaning binaries...$(RESET)"
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

run:
	make re && ./minishell

valgrind:
	$(LEAK) ./minishell

.PHONY: all run re clean fclean
