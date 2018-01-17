/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:39:45 by thugo             #+#    #+#             */
/*   Updated: 2018/01/17 17:39:57 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "lexer_types.h"

int		lexer_getnexttoken(t_token *tk, char **cmd, char **cur);
int		rules_comment(t_token *tk, char **cur);
int		rules_operator(t_token *tk, char **cur);
int		rules_reserved(t_token *tk, char **cur);
int		rules_io_number(t_token *tk, char **cur);
int		rules_assignment_word(t_token *tk, char **cur);
int		rules_word(t_token *tk, char **cur);

#endif
