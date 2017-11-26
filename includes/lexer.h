/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:37:22 by thugo             #+#    #+#             */
/*   Updated: 2017/11/26 19:38:31 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "lst.h"

typedef	enum		e_token_id
{
	WORD, OPERATOR, NEWLINE, AND_IF, OR_IF, DSEMI, DLESS, DGREAT, LESSAND,
	GREATAND, LESSGREAT, DLESSDASH, IO_NUMBER, AND, LPAR, RPAR, PIPE, GREAT,
	LESS, CLOBBER, SEMI
}					t_token_id;

typedef struct		s_operator
{
	char		*op;
	t_token_id	id;
}					t_operator;

typedef struct		s_token
{
	char		*begin;
	size_t		size;
	t_token_id	id;
}					t_token;

t_list				*lexer_tokenize(char *cmd);

#endif
