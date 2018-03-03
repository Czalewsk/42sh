# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thugo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/28 14:48:37 by thugo             #+#    #+#              #
#    Updated: 2018/02/15 09:08:15 by thugo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Binary
NAME = libunit.a
#GCC Flags
FLAGS = -Werror -Wall -Wextra
#Source files
SRC = register.c launcher.c init.c minilib/ml_lstnew.c minilib/ml_lstpush.c\
	  minilib/ml_nulltabdup.c minilib/ml_strnjoin.c minilib/ml_strnew.c display.c\
	  utils/utils_getline.c utils/utils_purgefd.c utils/utils_venv.c
#Dependance files
DEP = Makefile includes/libunit.h includes/libunit_types.h includes/minilib.h
OBJ = $(addprefix obj/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(DEP)
	@printf "\n[\e[33m$(NAME)\e[0m] \e[34mBuild:\e[0m $(NAME)"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf " [\e[32mOK\e[0m]\n"

obj/%.o: src/%.c
	@printf "[\e[33m$(NAME)\e[0m] \e[34mCompile:\e[0m $^\e[K\r"
	@mkdir -p $(dir $@)
	@gcc $(FLAGS) -I includes -c $^ -o $@
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

.PHONY: all clean fclean re
