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

typedef struct s_valid_res
{
	t_token_id	one;
	t_token_id	two;
}				t_valid_res;

typedef struct s_execpted
{
	t_token_id	one;
	t_token_id	two;
}

typedef struct s_reserved
{
	t_token_id	one;
//	int			(*res)(t_tree *current, char *cur, char *cmd);
}				t_reserved;

typedef struct s_while
{
	t_token_id	one;
	t_token_id	two;
	t_tree		*(*cmp)(t_tree *current, t_tree *new);
}				t_while;

typedef struct s_classic
{
	t_token_id	one;
	t_token_id	two;
	t_tree		*(*cmp)(t_tree *current, t_tree *new);
}				t_classic;

int		parse_while(t_tree *curr, char *cur, char *cmd);
int		parse_if(t_tree *curr, char *cur, char *cmd);
int		parse_until(t_tree *curr, char *cur, char *cmd);
int		parse_case(t_tree *curr, char *cur, char *cmd);

int							ft_free_token(t_tree *token);
int							ft_free_tree(t_tree *c);
int							add_in_classic_tree(t_tree *cur, t_tree *new);

int							parser(char	*cmd);

int							ft_fill_for_jobs(t_tree *head);

t_tree						*init_node(t_token c, t_tree *n);

t_tree						*init_node(t_token c, t_tree *n);
t_tree						*go_to_current_right(t_tree *cur, t_tree *new);
t_tree						*go_to_current_left(t_tree *cur, t_tree *new);

#endif