/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 16:41:07 by maastie           #+#    #+#             */
/*   Updated: 2018/02/28 19:15:26 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const t_check_proc g_check_procs[] = {
	{AND_IF, &check_and_if},
	{OR_IF, &check_or_if},
	{PIPE, &check_pipe},
	{0, NULL}
};

const t_fill_job	g_fill_jobs[] = {
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
	{AND, WORD, &go_to_current_left},
	{AND, SUBSH, &go_to_current_left},
	{AND, IO_NUMBER, &go_to_current_left},
	{AND_IF, WORD, &go_to_current_right},
	{AND_IF, SUBSH, &go_to_current_right},
	{AND_IF, IO_NUMBER, &go_to_current_right},
	{DLESS, WORD, &go_to_current_right},
	{DLESS, SUBSH, &go_to_current_right},
	{DGREAT, WORD, &go_to_current_right},
	{GREAT, WORD, &go_to_current_right},
	{GREATAND, WORD, &go_to_current_right},
	{IO_NUMBER, GREATAND, &go_to_current_right},
	{IO_NUMBER, SUBSH, &go_to_current_right},
	{IO_NUMBER, LESSAND, &go_to_current_right},
	{LESSAND, WORD, &go_to_current_right},
	{LESS, WORD, &go_to_current_right},
	{OR_IF, WORD, &go_to_current_right},
	{OR_IF, SUBSH, &go_to_current_right},
	{OR_IF, IO_NUMBER, &go_to_current_right},
	{PIPE, WORD, &go_to_current_right},
	{PIPE, SUBSH, &go_to_current_right},
	{PIPE, IO_NUMBER, &go_to_current_right},
	{SEMI, WORD, &go_to_current_left},
	{SEMI, SUBSH, &go_to_current_left},
	{SEMI, IO_NUMBER, &go_to_current_left},
	{SUBSH, AND, &go_to_current_right},
	{SUBSH, AND_IF, &go_to_current_right},
	{SUBSH, OR_IF, &go_to_current_right},
	{SUBSH, WORD, &go_to_current_right},
	{SUBSH, IO_NUMBER, &go_to_current_right},
	{SUBSH, PIPE, &go_to_current_right},
	{SUBSH, SEMI, &go_to_current_right},
	{SUBSH, SUBSH, &go_to_current_right},
	{SUBSH, DGREAT, &go_to_current_right},
	{SUBSH, DLESS, &go_to_current_right},
	{SUBSH, LESS, &go_to_current_right},
	{WORD, SUBSH, &go_to_current_right},
	{WORD, IO_NUMBER, &go_to_current_right},
	{WORD, DLESS, &go_to_current_right},
	{WORD, DGREAT, &go_to_current_right},
	{WORD, LESSAND, &go_to_current_right},
	{WORD, GREATAND, &go_to_current_right},
	{WORD, LESSGREAT, &go_to_current_right},
	{WORD, LESS, &go_to_current_right},
	{WORD, GREAT, &go_to_current_right},
	{WORD, AND_IF, &go_to_current_right},
	{WORD, OR_IF, &go_to_current_right},
	{WORD, AND, &go_to_current_right},
	{WORD, SEMI, &go_to_current_right},
	{WORD, PIPE, &go_to_current_right},
	{WORD, WORD, &go_to_current_right},
	{ASSIGNMENT_WORD, ASSIGNMENT_WORD, &go_to_current_right},
	{ASSIGNMENT_WORD, WORD, &go_to_current_right},
	{0, 0, NULL}
};
