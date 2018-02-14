/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 16:41:07 by maastie           #+#    #+#             */
/*   Updated: 2017/12/13 16:41:10 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const t_fill_job	g_fill_jobs[] = {
	{WORD, &add_in_arguments},
	{GREATAND, &gand},
	{LESSAND, &land},
	{IO_NUMBER, &modify_io},
	{GREAT, &ft_great},
	{LESS, &ft_less},
	{DLESS, &here_doc},
	{DGREAT, &ft_dgreat},
	{LESSGREAT, &lessgreat},
	//ASSIGNMENT_WORD, SUBSH
	{0, NULL}
};

const t_classic g_classics[] = {
	{SEMI, WORD, &go_to_current_left},
	{AND, WORD, &go_to_current_left},
	{AND_IF, WORD, &go_to_current_right},
	{OR_IF, WORD, &go_to_current_right},
	{PIPE, WORD, &go_to_current_right},
	{IO_NUMBER, GREATAND, &go_to_current_right},
	{IO_NUMBER, LESSAND, &go_to_current_right},
	{DLESS, WORD, &go_to_current_right},
	{DGREAT, WORD, &go_to_current_right},
	{LESSAND, WORD, &go_to_current_right},
	{GREATAND, WORD, &go_to_current_right},
	{DLESSDASH, WORD, &go_to_current_right},
	{LESSGREAT, WORD, &go_to_current_right},
	{CLOBBER, WORD, &go_to_current_right},
	{LESS, WORD, &go_to_current_right},
	{GREAT, WORD, &go_to_current_right},
	{AND, IO_NUMBER, &go_to_current_left},
	{AND_IF, IO_NUMBER, &go_to_current_right},
	{OR_IF, IO_NUMBER, &go_to_current_right},
	{PIPE, IO_NUMBER, &go_to_current_right},
	{SEMI, IO_NUMBER, &go_to_current_left},
	{WORD, IO_NUMBER, &go_to_current_right},
	{WORD, DLESS, &go_to_current_right},
	{WORD, DGREAT, &go_to_current_right},
	{WORD, LESSAND, &go_to_current_right},
	{WORD, GREATAND, &go_to_current_right},
	{WORD, DLESSDASH, &go_to_current_right},
	{WORD, LESSGREAT, &go_to_current_right},
	{WORD, CLOBBER, &go_to_current_right},
	{WORD, LESS, &go_to_current_right},
	{WORD, GREAT, &go_to_current_right},
	{WORD, AND_IF, &go_to_current_right},
	{WORD, OR_IF, &go_to_current_right},
	{WORD, AND, &go_to_current_right},
	{WORD, SEMI, &go_to_current_right},
	{WORD, PIPE, &go_to_current_right},
	{WORD, WORD, &go_to_current_right},
	{0, 0, NULL}
};
