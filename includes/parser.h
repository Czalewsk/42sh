/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:32:01 by maastie           #+#    #+#             */
/*   Updated: 2017/11/26 18:32:02 by maastie          ###   ########.fr       */
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



void						reset_fd(int pdes[2], t_process *p);
int							set_for_pipe(t_tree *c);
int							ft_leave_parse(t_token t);
int							read_parser(char **cmd, char *cur);
int							cnewline(t_token t, char **cmd, char *cur);
int							read_from_prompt(char **cmd, char *cur);
int							ft_free_token(t_tree *token);
int							ft_free_array(char **argv);
int							ft_free_tree(t_tree *c);
int							ft_free_process(t_process *p);
int							add_in_classic_tree(t_tree *cur, t_tree *new);
int							parser(char	**cmd);
int							execute_run(t_tree *c, t_tree *stop);
int							ft_fill_for_jobs(t_tree *head);
char						*get_command(char *ret, t_tree *chead);
void						set_new_id(t_tree *cur, t_tree *new);
void						init_closefd(int pdes[2]);

t_process					*init_process(t_process *p);
t_tree						*init_node(t_token c, t_tree *n);
t_tree 						*set_data_for_fill(t_tree *c, t_process *p);
t_tree						*pipe_process(t_process *p, t_tree *clist);
t_tree						*modify_io(t_process *p, t_tree *clist);
t_tree						*set_end(t_process *p, t_tree *clist);
t_tree						*add_in_arguments(t_process *p, t_tree *clist);
t_tree						*go_to_current_right(t_tree *cur, t_tree *new);
t_tree						*go_to_current_left(t_tree *cur, t_tree *new);
t_tree						*ft_dgreat(t_process *p, t_tree *c);
t_tree						*ft_great(t_process *p, t_tree *c);
t_tree						*ft_less(t_process *p, t_tree *c);
t_tree						*land(t_process *p, t_tree *c);
t_tree						*gand(t_process *p, t_tree *c);

#endif