/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:26:48 by thugo             #+#    #+#             */
/*   Updated: 2017/12/07 14:09:20 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ast_types.h"

int		lexer_getnexttoken(t_token *tk, char **cmd, char **cur);
int		lexer_tokenize(t_token *token, char **cur, size_t *cursize);
int		quote_isescape(char *qstat, char c);

#endif
