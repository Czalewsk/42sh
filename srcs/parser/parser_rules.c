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

// const t_fd_action	g_fd_action[] = {
// 	{ANDGREAT, &and_great},
// 	{DLESS, &here_doc},
// 	{DGREAT, &dgreat},
// 	{GREATAND, &great_and},
// 	{GREAT, &great},
// 	{LESS, &less},
// }

const t_cmd_action	g_cmd_actions[] = {
	{WORD, &add_in_arguments},
	{IO_NUMBER, &modify_io},
	{GREATAND, &set_fd_in_process},
	{LESSAND, &set_fd_in_process},
	{LESS, &set_fd_in_process},
	{GREAT, &set_fd_in_process},
	{LESSGREAT, &set_fd_in_process},
//	{DLESS, &set_fd_by_here},
	{DGREAT, &set_fd_in_process},
	{SUBSH, &subshell},
	{ASSIGNMENT_WORD, &assign_word},
	{0, NULL}
//	{ANDGREAT, &set_fd_in_process},
};

const t_classic g_classics[] = {


	{AND, LESSGREAT, &go_to_current_left, NULL},
	{SEMI, LESSGREAT, &go_to_current_left, NULL},

	{LESSGREAT, WORD, &go_to_current_right, NULL},
	{IO_NUMBER, LESSGREAT, &go_to_current_right, NULL},
	{WORD, LESSGREAT, &go_to_current_right, NULL},
	{AND_IF, LESSGREAT, &go_to_current_right, NULL},
	{OR_IF, LESSGREAT, &go_to_current_right, NULL},
	{PIPE, LESSGREAT, &go_to_current_right, NULL},
	{SUBSH, LESSGREAT, &go_to_current_right, NULL},

//	{ANDGREAT, WORD, &go_to_current_right, NULL},
	{AND, WORD, &go_to_current_left, NULL},
	{AND, SUBSH, &go_to_current_left, NULL},
	{AND, IO_NUMBER, &go_to_current_left, NULL},
	{AND, LESSAND, &go_to_current_left, NULL},
	{AND, GREATAND, &go_to_current_left, NULL},
	{AND, ANDGREAT, &go_to_current_left, NULL},
	{AND_IF, WORD, &go_to_current_right, NULL},
	{AND_IF, SUBSH, &go_to_current_right, NULL},
	{AND_IF, IO_NUMBER, &go_to_current_right, NULL},
//	{AND_IF, ANDGREAT, &go_to_current_left, NULL},
	{DLESS, WORD, &go_to_current_right, &here},
	{DLESS, SUBSH, &go_to_current_right, &here},
	{DGREAT, WORD, &go_to_current_right, NULL},
	{GREAT, WORD, &go_to_current_right, NULL},
	{GREAT, SUBSH, &go_to_current_right, NULL},
	{GREATAND, WORD, &go_to_current_right, NULL},
	{IO_NUMBER, GREAT, &go_to_current_right, NULL},
	{IO_NUMBER, GREATAND, &go_to_current_right, NULL},
	{IO_NUMBER, ANDGREAT, &go_to_current_right, NULL},
	{IO_NUMBER, SUBSH, &go_to_current_right, NULL},
	{IO_NUMBER, LESSAND, &go_to_current_right, NULL},
	{IO_NUMBER, LESS, &go_to_current_right, NULL},
	{LESSAND, WORD, &go_to_current_right, NULL},
	{LESSAND, IO_NUMBER, &go_to_current_right, NULL},
	{LESS, WORD, &go_to_current_right, NULL},
	{OR_IF, WORD, &go_to_current_right, NULL},
	{OR_IF, SUBSH, &go_to_current_right, NULL},
	{OR_IF, IO_NUMBER, &go_to_current_right, NULL},
	{OR_IF, LESSAND, &go_to_current_right, NULL},
	{OR_IF, GREATAND, &go_to_current_right, NULL},
//	{OR_IF, ANDGREAT, &go_to_current_right, NULL},
	{PIPE, WORD, &go_to_current_right, NULL},
	{PIPE, SUBSH, &go_to_current_right, NULL},
	{PIPE, IO_NUMBER, &go_to_current_right, NULL},
	{PIPE, LESSAND, &go_to_current_right, NULL},
	{PIPE, GREATAND, &go_to_current_right, NULL},
//	{PIPE, ANDGREAT, &go_to_current_right, NULL},
	{SEMI, WORD, &go_to_current_left, NULL},
	{SEMI, SUBSH, &go_to_current_left, NULL},
	{SEMI, IO_NUMBER, &go_to_current_left, NULL},
	{SEMI, LESSAND, &go_to_current_left, NULL},
//	{SEMI, GREATAND, &go_to_current_left, NULL},
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
	{SUBSH, LESSAND, &go_to_current_right, NULL},
	{SUBSH, GREATAND, &go_to_current_right, NULL},
//	{SUBSH, ANDGREAT, &go_to_current_right, NULL},
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
//	{WORD, ANDGREAT, &go_to_current_right, NULL},
	{WORD, AND, &go_to_current_right, NULL},
	{WORD, SEMI, &go_to_current_right, NULL},
	{WORD, PIPE, &go_to_current_right, NULL},
	{WORD, WORD, &go_to_current_right, NULL},
	{ASSIGNMENT_WORD, ASSIGNMENT_WORD, &go_to_current_right, NULL},
	{ASSIGNMENT_WORD, WORD, &go_to_current_right, NULL},
	{0, 0, NULL, NULL}
};
