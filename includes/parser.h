/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:32:01 by maastie           #+#    #+#             */
/*   Updated: 2018/03/21 14:07:55 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSER_H
# define __PARSER_H

# include "ft_sh.h"

typedef struct		s_tree
{
	struct s_tree			*father;
	struct s_tree			*previous;
	struct s_tree			*left;
	struct s_tree			*right;
	struct s_token			token;
}					t_tree;

typedef struct		s_cmd_action
{
	t_token_id	one;
	t_tree		*(*fjob)(t_process *p, t_tree *clist);
}					t_cmd_action;

typedef struct		s_valid_res
{
	t_token_id	one;
	t_token_id	two;
}					t_valid_res;

typedef struct		s_for_close
{
	t_token_id	one;
	t_token_id	two;
}					t_for_close;

typedef struct		s_execpted
{
	t_token_id	one;
	t_token_id	two;
}					t_execpted;

typedef struct		s_classic
{
	t_token_id	one;
	t_token_id	two;
	t_tree		*(*cmp)(t_tree *current, t_tree *new);
	t_tree		*(*here)(t_tree *current, t_tree *new);
}					t_classic;

typedef	struct		s_builtin
{
	char	*name;
	int		(*f)(t_process *p, int argc, char **argv, char **env);
}					t_builtin;

extern t_tree		*g_head_tree;
extern t_tree		*g_current;
extern t_list		*g_here_list;

char				**how_to_do(char **argv, char *cmd);
char				**add_to_argv(char **argv, char *to_add);
char				**concat_tab_for_sub(char **argv, char **k, int size);
char				**sub_shell_main(char **argv, char *cmd);
char				*add_it_spaced(char *dst, char *src);
char				*extrac_from_backtite(char *dst, char *ref);
t_job				*need_norme(t_job *j);
t_job				*get_new_job(t_tree *c, int exit_status, int fg);
t_job				*create_new_job(t_tree *c);
t_tree				*cpy_from_tree(t_tree *c);
t_tree				*next_on_tree(t_tree *c, int exit_status);
t_tree				*split_cmd_jobs(t_tree *c, int if_fg);
t_tree				*execute_run(t_tree *c, t_job *job, t_list *lst);
t_tree				*new_success_or_if(t_tree *c);
t_tree				*get_new_from_failure_and(t_tree *c);
int					exec_with_acces(char *t, t_process *p, t_job *j, char **e);
int					executor(t_job *j, t_process *p,
	int pipe[2][2], char **env);
int					exec_in_line(t_job *job, char **env);
int					get_id_max_job();
void				pere(t_job *j, t_process *pr, int p[2][2], char **env);
void				modify_io_child(t_process *p,
	int pipe[2][2], int pr, int dr);
void				print_process(t_process *p);
void				put_job_at_head_in_job_order(t_job *job);
void				put_job_at_end_in_first_job(t_job *job);
void				print_first_job();
void				print_job_order();
void				print_job(t_job *job);
void				execute_job(t_job *job);
void				wait_multiple_proc(t_list *pid_list, t_job *job);
pid_t				init_pipe_run(pid_t f, int p[2][2], t_tree *c, t_tree *e);
void				dup_and_close_son_pipe(t_tree *c, t_tree *e,
		int p[2][2], t_list *pid_list);
void				init_current_process(t_tree *c, t_job *job);
void				execute_job_with_fork(t_job *j, char **env);
int					clear_execute(char **path, t_process *p);
int					do_built_in(t_process *p, char **env);
int					set_for_pipe(t_tree *c, t_job *job);
int					read_parser(char **cmd, char *cur);
int					cnewline(t_token t, char **cmd, char **cur);
int					read_from_prompt(char **cmd, char **cur);
int					ft_free_node(t_tree *token);
int					ft_free_array(char **argv);
int					ft_free_tree(t_tree *c);
int					ft_free_process(t_process *p);
int					add_in_classic_tree(t_tree *cur, t_tree *new);
int					parser(char	**cmd);
int					ft_fill_for_jobs(t_tree *head);
char				*get_command(char *ret, t_tree *chead);
char				**get_new_argv(char **argv, char *to_add);
char				**extract_from_tab(char **env, char *ref);
t_process			*init_process(t_process *p);
t_tree				*here(t_tree *current, t_tree *new);
t_tree				*init_node(t_token c, t_tree *n);
t_tree				*subshell(t_process *p, t_tree *c);
t_tree				*set_data_for_fill(t_tree *c, t_process *p);
t_tree				*modify_io(t_process *p, t_tree *clist);
t_tree				*add_in_arguments(t_process *p, t_tree *clist);
t_tree				*go_to_current_right(t_tree *cur, t_tree *new);
t_tree				*go_to_current_left(t_tree *cur, t_tree *new);
t_tree				*here_doc(t_process *p, t_tree *c);
t_tree				*ft_dgreat(t_process *p, t_tree *c);
t_tree				*ft_great(t_process *p, t_tree *c);
t_tree				*ft_less(t_process *p, t_tree *c);
t_tree				*land(t_process *p, t_tree *c);
t_tree				*gand(t_process *p, t_tree *c);
t_tree				*lessgreat(t_process *p, t_tree *c);
t_tree				*clobber(t_process *p, t_tree *c);
void				clear_assign_word(t_tree *cur, t_tree *new);

#endif
