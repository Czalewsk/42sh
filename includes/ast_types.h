/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:26:31 by thugo             #+#    #+#             */
/*   Updated: 2017/12/04 20:18:01 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_TYPES_H
# define AST_TYPES_H

# include <sys/types.h>

typedef	enum		e_token_id
{
	WORD = 0, NEWLINE, AND_IF, OR_IF, DSEMI, DLESS, DGREAT, LESSAND,
	GREATAND, LESSGREAT, DLESSDASH, IO_NUMBER, AND, LPAR, RPAR, PIPE, GREAT,
	LESS, CLOBBER, SEMI, If, Then, Else, Elif, Fi, Do, Done, Case, Esac, While,
	Until, For
}					t_token_id;

typedef enum		e_token_type
{
	OPERATOR = 0, RESERVED = 1
}					t_token_type;

typedef struct		s_astrule
{
	char			*op;
	t_token_id		id;
	t_token_type	type;
}					t_astrule;

typedef struct		s_token
{
	char		*str;
	size_t		size;
	t_token_id	id;
}					t_token;

#endif
