# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 16:49:39 by bviala            #+#    #+#              #
#    Updated: 2018/03/29 04:01:07 by czalewsk         ###   ########.fr        #
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
FLAGS			= -Wall -Wextra -Werror -g -fsanitize=address
#------------------------------------------------------------------------------#

#---------------------------------| INCLUDES |---------------------------------#
SRCS_PATH		= srcs/
OBJS_PATH		= objs/
INCLUDES_PATH	= includes/
LIBFT_PATH		= libft/includes/
#------------------------------------------------------------------------------#

#------------------------------| SOURCE FILES |--------------------------------#
SRCS_FILES		= ft_sh 													\
				  termcaps/termcaps_init termcaps/termcaps_comp				\
				  prompt/prompt_display prompt/prompt_add					\
				  prompt/prompt_git											\
				  edition/buff_handler edition/read							\
				  edition/key_manager edition/insert_char edition/cursor	\
				  edition/unicode edition/print edition/curs_back			\
				  edition/expansion_wrapper edition/wrapper_is_arg			\
				  edition/curs_word											\
				  builtins/builtin_history builtins/history_expoint			\
				  builtins/builtin_export builtins/builtin_unsetenv			\
				  builtins/builtin_setenv builtins/builtin_history2			\
				  builtins/builtin_exit builtins/builtin_echo				\
				  builtins/builtin_cd builtins/history_expoint2				\
				  builtins/builtin_env										\
				  history/history_mode history/history_noaccess				\
				  history/history_utils	history/history_search				\
				  history/history_ctrlr	history/history_ctrlr_tools			\
				  history/change_mode										\
				  completion/sh_comp completion/change_mode					\
				  completion/print_comp completion/add_select				\
				  completion/add_dir completion/sh_first_comp				\
				  completion/add_bin completion/add_env						\
				  completion/prompt_comp completion/arrow_comp				\
				  completion/signal_comp completion/comp_tools				\
				  lexer/tokenize lexer/rules lexer/rules_fn1				\
				  lexer/rules_fn2											\
				  expansions/expand expansions/parameters					\
				  expansions/tilde expansions/globing						\
				  expansions/history_expoint								\
				  env/init env/assign_word env/get env/set env/make env/len	\
				  env/unset env/destroy										\
				  utils/escape/escape_functions utils/escape/sh_escape		\
				  utils/escape/escape_dquote utils/escape/escape_it			\
				  utils/sh_error utils/fds_utils utils/update_display		\
				  utils/stats_check utils/cwd utils/find_path				\
				  utils/find_cdpath											\
				  utils/fd													\
				  glob/brace_expansion glob/brace_valide_type				\
				  glob/brace_fill_seq glob/brace_find glob/brace_expand		\
				  glob/glob_buff_handler glob/glob_path glob/glob			\
				  glob/glob_add_rules glob/glob_rules glob/glob_rules_square\
				  glob/glob_folders glob/glob_rules_check glob/glob_files	\
				  glob/globbing												\
				  glob/glob_free_function glob/glob_is_relative				\
				  parser/parser parser/parser_rules parser/free_parser		\
				  parser/fill_for_jobs parser/add_in_tree parser/fd			\
				  parser/tools_for_fill parser/init parser/execution		\
				  parser/fill_for_jobs2 parser/tools_for_fill2				\
				  parser/modify_io parser/add_in_arguments 					\
				  parser/read_from_prompt parser/jobs parser/fd2			\
				  parser/heredoc parser/call_built_in parser/subshell		\
				  parser/clear_assign_word parser/subshell_tools			\
				  parser/exec_tools											\
				  paste/paste_handler paste/pasted_remove_highlight			\
				  paste/cpy_pste_intern paste/paste_handler_utils			\
				  jobControl/bt_bg											\
				  jobControl/bt_fg											\
				  jobControl/bt_jobs										\
				  jobControl/continue_job									\
				  jobControl/do_job_notification							\
				  jobControl/get_job										\
				  jobControl/jc_process_display								\
				  jobControl/job_display									\
				  jobControl/job_status										\
				  jobControl/mark_job_as_running							\
				  jobControl/mark_process_status							\
				  jobControl/put_job_in_background							\
				  jobControl/put_in_foreground								\
				  jobControl/update_status									\
				  jobControl/wait_for_job									\
				  jobControl/init_job_control								\
				  jobControl/cpy_profonde_process							\
				  jobControl/launch_process									\
				  jobControl/put_first_in_job_order							\
				  jobControl/del_job										\
				  signal/signal_handler										\
				  signal/signal_sigchld										\
				  signal/signal_sigtstp										\
				  signal/signal_sigttou										\
				  signal/signal_sigttin										\
				  signal/signal_handler signal/signal_sigint signal/sigwinch\
				  signal/signal_avoid signal/signal_sigcont
#------------------------------------------------------------------------------#

#-------------------------------| HEADER FILES |-------------------------------#
HEAD_FILES		= ft_sh.h builtins.h edition.h history.h prompt.h termcaps.h\
				  utils.h sh_escape.h lexer_types.h lexer.h completion.h	\
				  expansions.h sh_signal.h job_control.h env.h
#------------------------------------------------------------------------------#

#------------------------------| CREATE SOURCE |-------------------------------#
SRCS			= $(addprefix $(SRCS_PATH), $(addsuffix .c, $(SRCS_FILES)))
#------------------------------------------------------------------------------#

#------------------------------| CREATE OBJECTS |------------------------------#
OBJS_DIRS		= $(addprefix $(OBJS_PATH), termcaps/ prompt/ edition/ utils/ \
 utils/escape/ glob/ builtins/ history/ lexer/ completion/ paste/ expansions/ \
 parser/ env/ signal/ jobControl/)
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

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS) $(HEADERS_LIBFT) Makefile
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
