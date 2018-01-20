/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:40:22 by thugo             #+#    #+#             */
/*   Updated: 2018/01/18 20:07:52 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TYPES_H
# define LEXER_TYPES_H

# include <sys/types.h>

typedef	enum		e_token_id
{
	WORD = 0, NEWLINE, AND_IF, OR_IF, DSEMI, DLESS, DGREAT, LESSAND,
	GREATAND, LESSGREAT, DLESSDASH, AND, LPAR, RPAR, PIPE, GREAT,
	LESS, CLOBBER, SEMI, If, Then, Else, Elif, Fi, Do, Done, Case, Esac, While,
	Until, For, IO_NUMBER, ASSIGNMENT_WORD
}					t_token_id;

typedef struct		s_token_assign
{
	char			*op;
	t_token_id		id;
}					t_token_assign;

typedef struct		s_token
{
	char		*str;
	size_t		size;
	t_token_id	id;
}					t_token;

#endif
