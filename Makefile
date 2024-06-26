# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 15:36:20 by jlu               #+#    #+#              #
#    Updated: 2024/04/18 17:44:25 by jlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = pipex
NAME = pipex

LIBFT = ./libft/libft.a	

SRC = ./SRC/pipe_x.c \
	  ./SRC/pipex_utils.c \

BSRC = ./BSRC/pipex_bonus.c \
	   ./BSRC/child_bonus.c \
	   ./BSRC/child_supp_bonus.c \
	   ./BSRC/util_bonus.c \
	   ./BSRC/heredoc_bonus.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror

#Color ANSI Code
BOLD   := \033[1m./SRC/
RED    := \033[31;1m
GREEN  := \033[32;1m
YELLOW := \033[33;1m
BLUE   := \033[34;1m
MAGENTA   := \033[35;1m
CYAN      := \033[36;1m
WHITE     := \033[37;1m
RESET     := \x1b[0m #reseting the text formatting to default state

OBJECTS_DIR = obj
OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(notdir $(SRC:.c=.o)))
BOBJECTS = $(addprefix $(OBJECTS_DIR)/,$(notdir $(BSRC:.c=.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
		@echo "Compiled with $(BLUE)$(CFLAGS)$(RESET)"
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT)
		@echo "$(CYAN)--------------------------------"
		@echo "$(NAME) = Let's get piping!"
		@echo "$(CYAN)--------------------------------$(RESET)"
		@rm -f $(BOBJECTS)
		@rm -f .bonus

$(LIBFT):
		@$(MAKE) -C ./libft

$(OBJECTS_DIR)/%.o: ./SRC/%.c
		@mkdir -p $(OBJECTS_DIR)
		@echo "Compiled $(GREEN) $^ $(RESET)"
		@$(CC) $(CFLAGS) -c -o $@ $^

bonus: $(BSRC) .bonus

.bonus: $(LIBFT) $(BOBJECTS)
		@echo "Compiled with $(BLUE)$(CFLAGS)$(RESET)"
		@touch .bonus
		@$(CC) $(CFLAGS) $(BOBJECTS) $(LIBFT) -o $(NAME)
		@echo "$(CYAN)--------------------------------"
		@echo "$(NAME) = you have activated my bonus 😏!"
		@echo "$(CYAN)--------------------------------$(RESET)"
		@rm -f $(OBJECTS)

$(OBJECTS_DIR)/%.o: ./BSRC/%.c
		@mkdir -p $(OBJECTS_DIR)
		@echo "Compiled $(GREEN) $^ $(RESET)"
		@$(CC) $(CFLAGS) -c -o $@ $^

clean:
		@$(MAKE) clean -C ./libft
		@rm -rf $(OBJECTS_DIR)/*.o
		@rm -rf .bonus
		@rm -rf .here_doc_temp
		@rm -rf obj
		@echo "$(WHITE) $(OBJECTS_DIR) $(GREEN) REMOVED"

fclean: clean
		@$(MAKE) fclean -C ./libft
		@rm -rf $(NAME)
		@echo "$(WHITE) $(PROJECT) $(RESET) $(GREEN) SO CLEANED"

re: fclean all

.PHONY: all clean fclean re bonus