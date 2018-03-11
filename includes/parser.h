/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:32:01 by maastie           #+#    #+#             */
/*   Updated: 2018/03/11 18:45:37 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSER_H
#define __PARSER_H

#include "ft_sh.h"

struct	s_tree				*head_tree;
struct	s_tree				*current;

typedef struct				s_tree
{
	struct s_tree			*father;
	struct s_tree			*previous;
	struct s_tree			*left;
	struct s_tree			*right;
	struct s_token			token;
}							t_tree;

typedef struct s_check_proc
{
	t_token_id	one;
	t_tree		*(*cproc)(t_tree *c, t_tree *s, t_job *job);
}				t_check_proc;

typedef struct s_fill_job
{
	t_token_id	one;
	t_tree		*(*fjob)(t_process *p, t_tree *clist);
}				t_fill_job;

typedef struct s_valid_res
{
	t_token_id	one;
	t_token_id	two;
}				t_valid_res;

typedef struct s_for_close
{
	t_token_id	one;
	t_token_id	two;
}				t_for_close;

typedef struct s_execpted
{
	t_token_id	one;
	t_token_id	two;
}				t_execpted;

typedef struct s_classic
{
	t_token_id	one;
	t_token_id	two;
	t_tree		*(*cmp)(t_tree *current, t_tree *new);
}				t_classic;

typedef	struct	s_builtin
{
	char	*name;
	int		(*f)(t_process *p, int argc, char **argv, char **env);
}				t_builtin;

int							clear_execute(char **path, t_process *p);
int							do_built_in(t_process *p, char **env);
int							set_for_pipe(t_tree *c, t_job *job);
int							ft_leave_parse(t_token t);
int							read_parser(char **cmd, char *cur);
int							cnewline(t_token t, char **cmd, char *cur);
int							read_from_prompt(char **cmd, char *cur);
int							ft_free_order(t_list *lst);
int							ft_free_node(t_tree *token);
int							ft_free_array(char **argv);
int							ft_free_tree(t_tree *c);
int							ft_free_process(t_process *p);
int							add_in_classic_tree(t_tree *cur, t_tree *new);
int							parser(char	**cmd);
int							execute_run(t_tree *c, t_tree *stop, t_job *job);
int							ft_fill_for_jobs(t_tree *head);

char						*get_command(char *ret, t_tree *chead);
char						**get_new_argv(char **argv, char *to_add);
char						**extract_from_tab(char **env, char *ref);

void						ft_need_jobs(t_tree *c);
t_job						*ft_create_jobs(t_tree *c);
void						reset_fd(int pdes[3], t_process *p);
void						init_closefd(int pdes[3]);

t_process					*init_process(t_process *p);
t_tree						*init_node(t_token c, t_tree *n);
t_tree						*subshell(t_process *p, t_tree *c);
t_tree 						*set_data_for_fill(t_tree *c, t_process *p);
t_tree						*pipe_process(t_process *p, t_tree *clist);
t_tree						*modify_io(t_process *p, t_tree *clist);
t_tree						*set_end(t_process *p, t_tree *clist);
t_tree						*add_in_arguments(t_process *p, t_tree *clist);
t_tree						*go_to_current_right(t_tree *cur, t_tree *new);
t_tree						*go_to_current_left(t_tree *cur, t_tree *new);
t_tree						*here_doc(t_process *p, t_tree *c);
t_tree						*ft_dgreat(t_process *p, t_tree *c);
t_tree						*ft_great(t_process *p, t_tree *c);
t_tree						*ft_less(t_process *p, t_tree *c);
t_tree						*land(t_process *p, t_tree *c);
t_tree						*gand(t_process *p, t_tree *c);
t_tree						*lessgreat(t_process *p, t_tree *c);
t_tree						*clobber(t_process *p, t_tree *c);
t_tree						*check_and_if(t_tree *tmp, t_tree *stop, t_job *job);
t_tree						*check_or_if(t_tree *tmp, t_tree *stop, t_job *job);
t_tree						*check_pipe(t_tree *tmp, t_tree *stop, t_job *job);
t_tree						*check_run_v2(t_tree *c, t_job *job);

void						clear_assign_word(t_tree *cur, t_tree *new);
#endif
