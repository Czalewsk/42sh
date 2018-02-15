# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thugo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/28 14:48:37 by thugo             #+#    #+#              #
#    Updated: 2018/02/15 22:02:59 by thugo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Binary
NAME = unit_test
#GCC Flags
FLAGS = -Werror -Wall -Wextra -g -fsanitize=address
#Includes Folders
INCLUDES = -I includes -I ../../includes -I ../../libft/includes
#Link library
LINKS = -L ../../libft -lft
#Tests Folders
TFOLDERS = expansions
#Source files
SRC = main.c $(wildcard ../../srcs/expansions/*.c)
#Dependance files
DEP = Makefile $(wildcard */*.h)

SRC += $(foreach dirs, $(TFOLDERS), $(wildcard $(dirs)/*.c))
OBJ = $(addprefix obj/, $(SRC:.c=.o))
INCLUDES += $(foreach dirs, $(TFOLDERS), -I $(dirs)) -I ../framework/includes
LINKS += -L../framework -lunit

all: $(NAME)

run: $(NAME)
	@./$(NAME)

$(NAME): $(OBJ) $(DEP)
	@printf "\n"
	@make -C ../../libft
	@printf "\n[\e[33m$(NAME)\e[0m] \e[34mBuild:\e[0m $(NAME)"
	@gcc $(OBJ) -o $(NAME) $(FLAGS) $(LINKS)
	@printf " [\e[32mOK\e[0m]\n"

obj/%.o: %.c
	@printf "[\e[33m$(NAME)\e[0m] \e[34mCompile:\e[0m $^\e[K\r"
	@mkdir -p $(dir $@)
	@gcc $(INCLUDES) $(FLAGS) -c $^ -o $@
	@printf "[\e[33m$(NAME)\e[0m] \e[34mCompile:\e[0m $^ [\e[32mOK\e[0m]\e[K\r"

clean:
	@printf "[\e[33m$(NAME)\e[0m] \e[34mDelete objects\e[0m"
	@rm -f $(OBJ)
	@rm -rf obj
	@printf " [\e[32mOK\e[0m]\n"

fclean: clean
	@printf "[\e[33m$(NAME)\e[0m] \e[34mDelete binary\e[0m"
	@rm -f $(NAME)
	@printf " [\e[32mOK\e[0m]\n"

re: fclean all

.PHONY: all run clean fclean re
