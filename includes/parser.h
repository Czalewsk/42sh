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
struct  s_imb				*imb;

typedef struct				s_imb
{
	struct s_tree			*reserved_node;
	struct s_tree			*end_of_reserved;
	struct s_imb			*old;
	struct s_imb			*next;
}							t_imb;

typedef struct				s_tree
{
	struct s_tree			*father;
	struct s_tree			*left;
	struct s_tree			*right;
	struct s_token			token;
}							t_tree;

typedef struct s_close_imb
{
	t_token_id	one;
	t_token_id	two;
	t_token_id	three;
}				t_close_imb;

typedef struct s_excepted
{
	t_token_id	one;
	t_token_id	two;	
}				t_excepted;

typedef struct	s_valid
{
	t_token_id	id;
	t_token_id	valid;
}				t_valid;

typedef struct	s_modify
{
	t_token_id	id;
}				t_modify;

typedef struct s_reserved
{
	t_token_id	id;
	t_token_id	end_id;
}				t_reserved;

typedef struct s_compatibilitytree
{
	t_token_id				id;
	t_tree					*(*cmp)(t_tree *current, t_tree *new);

}				t_compatibilitytree;

int							parser(char	*cmd);
t_tree						*init_node(t_token c, t_tree *n);



t_tree						*cmpand_if(t_tree *current, t_tree *new);
t_tree						*cmpand(t_tree *current, t_tree *new);
t_tree						*cmplpar(t_tree *current, t_tree *new);
t_tree						*cmprpar(t_tree *current, t_tree *new);
t_tree						*cmpdsemi(t_tree *current, t_tree *new);
t_tree						*cmpsemi(t_tree *current, t_tree *new);
t_tree						*cmpnewline(t_tree *current, t_tree *new);
t_tree						*cmpor_if(t_tree *current, t_tree *new);
t_tree						*cmppipe(t_tree *current, t_tree *new);
t_tree						*cmpdless(t_tree *current, t_tree *new);
t_tree						*cmpdgreat(t_tree *current, t_tree *new);
t_tree						*cmplessand(t_tree *current, t_tree *new);
t_tree						*cmpgreatand(t_tree *current, t_tree *new);
t_tree						*cmpdlessdash(t_tree *current, t_tree *new);
t_tree						*cmplessgreat(t_tree *current, t_tree *new);
t_tree						*cmpclobber(t_tree *current, t_tree *new);
t_tree						*cmpless(t_tree *current, t_tree *new);
t_tree						*cmpgreat(t_tree *current, t_tree *new);
t_tree						*cmpif(t_tree *current, t_tree *new);
t_tree						*cmpthen(t_tree *current, t_tree *new);
t_tree						*cmpelse(t_tree *current, t_tree *new);
t_tree						*cmpelif(t_tree *current, t_tree *new);
t_tree						*cmpfi(t_tree *current, t_tree *new);
t_tree						*cmpdo(t_tree *current, t_tree *new);
t_tree						*cmpdone(t_tree *current, t_tree *new);
t_tree						*cmpcase(t_tree *current, t_tree *new);
t_tree						*cmpesac(t_tree *current, t_tree *new);
t_tree						*cmpwhile(t_tree *current, t_tree *new);
t_tree						*cmpuntil(t_tree *current, t_tree *new);
t_tree						*cmpfor(t_tree *current, t_tree *new);
t_tree						*cmpword(t_tree *current, t_tree *new);

#endif