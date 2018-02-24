/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:23:47 by thugo             #+#    #+#             */
/*   Updated: 2018/02/23 11:02:03 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "lexer_types.h"
# include "libft.h"

typedef struct	s_expands_rules
{
	char		(*fn)(const t_token *, t_list **);
	int			sizeallowed;
	t_token_id	allowed[10];
}				t_expands_rules;

char			expansions_expand(t_list **lst, const t_token *tk);
void			expansions_addtoken(t_list **lst, char *str, t_token_id id);
char			expand_parameters(const t_token *tk, t_list **lst);
char			expand_tilde(const t_token *tk, t_list **lst);
char			expand_globing(const t_token *tk, t_list **lst);

#endif
