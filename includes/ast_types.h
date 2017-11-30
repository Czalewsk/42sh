/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:26:31 by thugo             #+#    #+#             */
/*   Updated: 2017/11/30 09:53:32 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_TYPES_H
# define AST_TYPES_H

# include <sys/types.h>

typedef	enum		e_token_id
{
	WORD, NEWLINE, AND_IF, OR_IF, DSEMI, DLESS, DGREAT, LESSAND,
	GREATAND, LESSGREAT, DLESSDASH, IO_NUMBER, AND, LPAR, RPAR, PIPE, GREAT,
	LESS, CLOBBER, SEMI
}					t_token_id;

typedef struct		s_astrule
{
	char		*op;
	t_token_id	id;
}					t_astrule;

typedef struct		s_token
{
	char		*str;
	t_token_id	id;
}					t_token;

#endif
