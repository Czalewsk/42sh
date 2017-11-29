/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:26:48 by thugo             #+#    #+#             */
/*   Updated: 2017/11/29 11:28:27 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ast_types.h"

# define QUOTE 1
# define DQUOTE 2
# define BACKSLASH 4

int					lexer_getnexttoken(t_token *token, char **cur);
int					quote_isescape(char *qstat, char c);

#endif
