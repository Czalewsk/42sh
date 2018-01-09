# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bviala <bviala@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 16:49:39 by bviala            #+#    #+#              #
#    Updated: 2017/11/30 14:36:16 by thugo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------| COLORS |-----------------------------------#
NOC				= \033[0m
RED				= \033[38;5;196m
GREEN			= \033[38;5;46m
YELLOW			= \033[38;5;226m
ORANGE			= \033[38;5;202m
#------------------------------------------------------------------------------#

#--------------------------------| LIBRARY |-----------------------------------#
NAME 			= 42sh
#------------------------------------------------------------------------------#

#-------------------------------| COMPILATION |--------------------------------#
CC				= gcc
FLAGS			= -Wall -Wextra -Werror -g
#------------------------------------------------------------------------------#

#---------------------------------| INCLUDES |---------------------------------#
SRCS_PATH		= srcs/
OBJS_PATH		= objs/
INCLUDES_PATH	= includes/
LIBFT_PATH		= libft/includes/
#------------------------------------------------------------------------------#

#------------------------------| SOURCE FILES |--------------------------------#
SRCS_FILES		= ft_sh \
				  termcaps/termcaps_init \
				  prompt/prompt_display \
				  edition/buff_handler edition/read edition/paste_handler \
				  edition/key_manager edition/insert_char edition/key_manager \
				  edition/cursor edition/unicode edition/print \
				  prompt/prompt_add \
				  ast/rules ast/lexer ast/lexer_tokenize \
				  parser/parser parser/compatibility parser/parser_rules \
				  parser/fill_for_jobs parser/free_parser parser/add_in_tree \
				  parser/reserved
#------------------------------------------------------------------------------#

#-------------------------------| HEADER FILES |-------------------------------#
HEAD_FILES		= ft_sh.h edition.h prompt.h termcaps.h ast.h ast_types.h parser.h
#------------------------------------------------------------------------------#

#------------------------------| CREATE SOURCE |-------------------------------#
SRCS			= $(addprefix $(SRCS_PATH), $(addsuffix .c, $(SRCS_FILES)))
#------------------------------------------------------------------------------#

#------------------------------| CREATE OBJECTS |------------------------------#
OBJS_DIRS		= $(addprefix $(OBJS_PATH), termcaps/ prompt/ edition/ ast/ parser/)
OBJ				= $(addprefix $(OBJS_PATH), $(addsuffix .o, $(SRCS_FILES)))
#------------------------------------------------------------------------------#

#-----------------------------------| LIBS |-----------------------------------#
LIBFT			= libft/libft.a
INCLUDES_LIBFT	= -I $(LIBFT_PATH)
HEADERS_LIBFT 	= $(addprefix $(LIBFT_PATH), libft.h)
#------------------------------------------------------------------------------#

#--------------------------------| INCLUDES |----------------------------------#
INCLUDES		= -I $(INCLUDES_PATH)
HEADERS			= $(addprefix $(INCLUDES_PATH), $(HEAD_FILES))
#------------------------------------------------------------------------------#
.PHONY	:	all clean fclean re


#----------------------------------| RULES |-----------------------------------#
all:
	@make -j -C libft/
	@make -j $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) -Llibft -lft -ltermcap $(FLAGS) $(INCLUDES) $(INCLUDES_LIBFT) $^ -o $(NAME)
		@printf "\r$(GREEN)✅  [$(NAME)] was succesfully created ✅$(NOC)\n"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS) $(HEADERS_LIBFT)
		@mkdir $(OBJS_PATH) 2> /dev/null || true
		@mkdir $(OBJS_DIRS) 2> /dev/null || true
		@$(CC) $(FLAGS) $(INCLUDES) $(INCLUDES_LIBFT) -o $@ -c $<
		@printf "$(notdir $@)... ☑️ $(NOC)\n"

clean:
		@make -C libft/ clean
		@if [ -e $(OBJS_PATH) ];\
		then\
			rm -rf $(OBJS_PATH);\
			printf "\r$(YELLOW)⚠️  Deleted object files ⚠️ \033[0m\033[K\n";\
		fi;

fclean: clean
		@make -C libft/ fclean
		@if [ -e $(NAME) ];\
		then\
			rm -rf $(NAME);\
			printf "\r$(RED)❌  Deleted [$(NAME)] ❌\033[0m\033[K\n";\
		fi;

re: fclean all
#------------------------------------------------------------------------------#
