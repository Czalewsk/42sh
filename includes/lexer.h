/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:39:45 by thugo             #+#    #+#             */
/*   Updated: 2018/03/10 16:08:09 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "lexer_types.h"

int		lexer_getnexttoken(t_token *tk, char **cur, char **cmd);
int		rules_comment(t_token *tk, char **cur, char *escape);
int		rules_operator(t_token *tk, char **cur, char *escape);
int		rules_reserved(t_token *tk, char **cur, char *escape);
int		rules_io_number(t_token *tk, char **cur, char *escape);
int		rules_assignment_word(t_token *tk, char **cur, char *escape);
int		rules_word(t_token *tk, char **cur, char *escape);
int		rules_escape(t_token *tk, char **cur, char *escape);
int		rules_subsh(t_token *tk, char **cur, char *escape);
int		rules_history_expoint(t_token *tk, char **cur, char *escape);

#endif
