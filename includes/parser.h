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
	struct s_tree			*father; // pere de la branche exemple ls -l -a | cat -e '|' est le pere de ls -l -a
	struct s_tree			*left;
	struct s_tree			*right;
	struct s_token			token;
}							t_tree;

typedef struct s_compatibilitytree
{
	t_token_id				id;
	t_tree					*(*cmp)(t_tree *current, t_token t);//atibility;

}				t_compatibilitytree;

int							parser(char	*cmd);
t_tree						*init_node(t_token c, t_tree *n);

t_tree						*cmpand_if(t_tree *current, t_token t);
t_tree						*cmpand(t_tree *current, t_token t);
t_tree						*cmplpar(t_tree *current, t_token t);
t_tree						*cmprpar(t_tree *current, t_token t);
t_tree						*cmpdsemi(t_tree *current, t_token t);
t_tree						*cmpsemi(t_tree *current, t_token t);
t_tree						*cmpnewline(t_tree *current, t_token t);
t_tree						*cmpor_if(t_tree *current, t_token t);
t_tree						*cmppipe(t_tree *current, t_token t);
t_tree						*cmpdless(t_tree *current, t_token t);
t_tree						*cmpdgreat(t_tree *current, t_token t);
t_tree						*cmplessand(t_tree *current, t_token t);
t_tree						*cmpgreatand(t_tree *current, t_token t);
t_tree						*cmpdlessdash(t_tree *current, t_token t);
t_tree						*cmplessgreat(t_tree *current, t_token t);
t_tree						*cmpclobber(t_tree *current, t_token t);
t_tree						*cmpless(t_tree *current, t_token t);
t_tree						*cmpgreat(t_tree *current, t_token t);
t_tree						*cmpif(t_tree *current, t_token t);
t_tree						*cmpthen(t_tree *current, t_token t);
t_tree						*cmpelse(t_tree *current, t_token t);
t_tree						*cmpelif(t_tree *current, t_token t);
t_tree						*cmpfi(t_tree *current, t_token t);
t_tree						*cmpdo(t_tree *current, t_token t);
t_tree						*cmpdone(t_tree *current, t_token t);
t_tree						*cmpcase(t_tree *current, t_token t);
t_tree						*cmpesac(t_tree *current, t_token t);
t_tree						*cmpwhile(t_tree *current, t_token t);
t_tree						*cmpuntil(t_tree *current, t_token t);
t_tree						*cmpfor(t_tree *current, t_token t);
t_tree						*cmpword(t_tree *current, t_token t);

#endif