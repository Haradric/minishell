#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/10 16:59:45 by mbraslav          #+#    #+#              #
#    Updated: 2017/04/10 16:59:46 by mbraslav         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
FLAGS = -Wall -Wextra -Werror
SOURCE =	main.c\
			input.c\
			check_input.c\
			environment.c\
			run_command.c\
			builtin_cd.c\
			builtin_echo.c\
			builtin_env.c\
			builtin_setenv.c\
			builtin_unsetenv.c\
			utils.c
OBJECT = $(SOURCE:.c=.o)
NAME = minishell
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJECT) $(LIBFT)
	$(CC) $(FLAGS) -o $@ $(OBJECT) $(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

$(LIBFT):
	make -C libft

clean:
	make clean -C ./libft
	rm -f $(OBJECT)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
