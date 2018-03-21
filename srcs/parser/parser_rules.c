/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 16:41:07 by maastie           #+#    #+#             */
/*   Updated: 2018/03/13 17:22:14 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const t_cmd_action	g_cmd_actions[] = {
	{WORD, &add_in_arguments},
	{GREATAND, &gand},
	{LESSAND, &land},
	{IO_NUMBER, &modify_io},
	{GREAT, &ft_great},
	{LESS, &ft_less},
	{DLESS, &here_doc},
	{DGREAT, &ft_dgreat},
	{SUBSH, &subshell},
	{ASSIGNMENT_WORD, &assign_word},
	{0, NULL}
};

const t_classic g_classics[] = {
	{AND, WORD, &go_to_current_left, NULL},
	{AND, SUBSH, &go_to_current_left, NULL},
	{AND, IO_NUMBER, &go_to_current_left, NULL},
	{AND_IF, WORD, &go_to_current_right, NULL},
	{AND_IF, SUBSH, &go_to_current_right, NULL},
	{AND_IF, IO_NUMBER, &go_to_current_right, NULL},
	{DLESS, WORD, &go_to_current_right, &here},
	{DLESS, SUBSH, &go_to_current_right, &here},
	{DGREAT, WORD, &go_to_current_right, NULL},
	{GREAT, WORD, &go_to_current_right, NULL},
	{GREAT, SUBSH, &go_to_current_right, NULL},
	{GREATAND, WORD, &go_to_current_right, NULL},
	{IO_NUMBER, GREAT, &go_to_current_right, NULL},
	{IO_NUMBER, GREATAND, &go_to_current_right, NULL},
	{IO_NUMBER, SUBSH, &go_to_current_right, NULL},
	{IO_NUMBER, LESSAND, &go_to_current_right, NULL},
	{IO_NUMBER, LESS, &go_to_current_right, NULL},
	{LESSAND, WORD, &go_to_current_right, NULL},
	{LESS, WORD, &go_to_current_right, NULL},
	{OR_IF, WORD, &go_to_current_right, NULL},
	{OR_IF, SUBSH, &go_to_current_right, NULL},
	{OR_IF, IO_NUMBER, &go_to_current_right, NULL},
	{PIPE, WORD, &go_to_current_right, NULL},
	{PIPE, SUBSH, &go_to_current_right, NULL},
	{PIPE, IO_NUMBER, &go_to_current_right, NULL},
	{SEMI, WORD, &go_to_current_left, NULL},
	{SEMI, SUBSH, &go_to_current_left, NULL},
	{SEMI, IO_NUMBER, &go_to_current_left, NULL},
	{SUBSH, AND, &go_to_current_right, NULL},
	{SUBSH, AND_IF, &go_to_current_right, NULL},
	{SUBSH, OR_IF, &go_to_current_right, NULL},
	{SUBSH, WORD, &go_to_current_right, NULL},
	{SUBSH, IO_NUMBER, &go_to_current_right, NULL},
	{SUBSH, PIPE, &go_to_current_right, NULL},
	{SUBSH, SEMI, &go_to_current_right, NULL},
	{SUBSH, SUBSH, &go_to_current_right, NULL},
	{SUBSH, DGREAT, &go_to_current_right, NULL},
	{SUBSH, DLESS, &go_to_current_right, NULL},
	{SUBSH, LESS, &go_to_current_right, NULL},
	{WORD, SUBSH, &go_to_current_right, NULL},
	{WORD, IO_NUMBER, &go_to_current_right, NULL},
	{WORD, DLESS, &go_to_current_right, NULL},
	{WORD, DGREAT, &go_to_current_right, NULL},
	{WORD, LESSAND, &go_to_current_right, NULL},
	{WORD, GREATAND, &go_to_current_right, NULL},
	{WORD, LESSGREAT, &go_to_current_right, NULL},
	{WORD, LESS, &go_to_current_right, NULL},
	{WORD, GREAT, &go_to_current_right, NULL},
	{WORD, AND_IF, &go_to_current_right, NULL},
	{WORD, OR_IF, &go_to_current_right, NULL},
	{WORD, AND, &go_to_current_right, NULL},
	{WORD, SEMI, &go_to_current_right, NULL},
	{WORD, PIPE, &go_to_current_right, NULL},
	{WORD, WORD, &go_to_current_right, NULL},
	{ASSIGNMENT_WORD, ASSIGNMENT_WORD, &go_to_current_right, NULL},
	{ASSIGNMENT_WORD, WORD, &go_to_current_right, NULL},
	{0, 0, NULL, NULL}
};
