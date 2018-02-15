/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:23:47 by thugo             #+#    #+#             */
/*   Updated: 2018/02/13 04:46:04 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "lexer_types.h"
# include "libft.h"

typedef struct	s_expands_rules
{
	void		(*fn)(t_token *, t_list **);
	int			sizeallowed;
	t_token_id	allowed[10];
}				t_expands_rules;

t_list			*expansions_expand(t_token *tk);
void			expansions_addtoken(t_list **lst, char *str, t_token_id);
void			expand_parameters(t_token *tk, t_list **lst);

#endif
