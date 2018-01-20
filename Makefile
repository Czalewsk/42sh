# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bviala <bviala@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 16:49:39 by bviala            #+#    #+#              #
#    Updated: 2018/01/12 16:15:36 by thugo            ###   ########.fr        #
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
SRCS_FILES		= ft_sh 													\
				  termcaps/termcaps_init 									\
				  prompt/prompt_display prompt/prompt_add					\
				  prompt/prompt_git											\
				  edition/buff_handler edition/read edition/paste_handler 	\
				  edition/key_manager edition/insert_char edition/cursor	\
				  edition/unicode edition/print edition/curs_back			\
				  utils/escape/escape_functions utils/escape/sh_escape		\
				  utils/escape/escape_dquote								\
				  glob/brace_expansion glob/brace_valide_type				\
				  glob/brace_fill_seq glob/brace_find glob/brace_expand		\
				  glob/glob_buff_handler									\
				  builtins/builtin_history									\
				  history/history_mode history/history_noaccess				\
				  history/history_utils	history/history_search				\
				  history/history_ctrlr										\
				  history/history_ctrlr_tools								\
				  ast/rules ast/lexer										\
				  parser/parser parser/compatibility parser/parser_rules	\
				  parser/fill_for_jobs parser/free_parser parser/add_in_tree\
				  parser/reserved parser/tools_for_fill_jobs parser/init	\
				  parser/modify_io parser/add_in_arguments					\
				  parser/read_from_prompt
#------------------------------------------------------------------------------#

#-------------------------------| HEADER FILES |-------------------------------#
HEAD_FILES		= ft_sh.h builtins.h edition.h history.h prompt.h termcaps.h\
				  utils.h sh_escape.h ast.h ast_types.h parser.h job_control.h
#------------------------------------------------------------------------------#

#------------------------------| CREATE SOURCE |-------------------------------#
SRCS			= $(addprefix $(SRCS_PATH), $(addsuffix .c, $(SRCS_FILES)))
#------------------------------------------------------------------------------#

#------------------------------| CREATE OBJECTS |------------------------------#
OBJS_DIRS		= $(addprefix $(OBJS_PATH), termcaps/ prompt/ edition/ utils/ \
					 utils/escape/ glob/ builtins/ history/ ast/ parser/)
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
