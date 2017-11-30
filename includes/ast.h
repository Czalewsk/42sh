/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:26:48 by thugo             #+#    #+#             */
/*   Updated: 2017/11/30 14:47:29 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ast_types.h"

int		lexer_getnexttoken(t_token *token, char **cur);
int		lexer_tokenize(t_token *token, char **cur, size_t *cursize);
int		quote_isescape(char *qstat, char c);

#endif
