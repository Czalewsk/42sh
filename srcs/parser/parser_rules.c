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

const t_for_close	g_for_closes[] = {
	{While, Done},
	{Until, Done},
	{Case, Esac},
	{If, Fi}
};

const t_execpted	g_execpteds[] = {
	{While, Do},
	{While, While},
	{If, If},
	{Do, Done},
	{If, Then},
	{Then, Elif},
	{Elif, Then},
	{Elif, Fi},
	{Else, Fi},
	{Until, Do},
	{Case, DSEMI},
	{DSEMI, DSEMI},
	{DSEMI, Esac}
};

const t_fill_job	g_fill_jobs[] = {
	{WORD, &add_in_arguments},
	{PIPE, &pipe_process},
	{IO_NUMBER, &modify_io},
	{AND_IF, &set_end},
	{OR_IF, &set_end},
	{AND, &set_end},
	{SEMI, &set_end},
	{0, NULL}
	// {While, &shellscript},
	// {If, &shellscript},
//	{LPAR, &subshell_capability},
};

const t_valid_res g_valid_ress[] = {
	{SEMI, While},
	{SEMI, If},
	{While, While},
	{While, If},
	{If, While},
	{SEMI, Case},
	{If, If},
	{While, Case}
};

const t_classic g_classics[] = {
// {While, While, &go_to_current_right},
// {While, If, &go_to_current_right},
// {While, WORD},
// {Do, WORD},
	{SEMI, WORD, &go_to_current_left},
//	{Done, SEMI},
//	{Do, SEMI},
//	{SEMI, Do},
//	{SEMI, Done},
	{AND, WORD, &go_to_current_left},
	{AND_IF, WORD, &go_to_current_left},
	{OR_IF, WORD, &go_to_current_left},
	{PIPE, WORD, &go_to_current_right},
	{AND, While, &go_to_current_right},
	{AND_IF, While, &go_to_current_left},
	{OR_IF, While, &go_to_current_left},
//	{PIPE, While},
//	{SEMI, While},
	{DLESS, WORD, &go_to_current_right},
	{DGREAT, WORD, &go_to_current_right},
	{LESSAND, WORD, &go_to_current_right},
	{GREATAND, WORD, &go_to_current_right},
	{DLESSDASH, WORD, &go_to_current_right},
	{LESSGREAT, WORD, &go_to_current_right},
	{CLOBBER, WORD, &go_to_current_right},
	{LESS, WORD, &go_to_current_right},
	{GREAT, WORD, &go_to_current_right},
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
// {Case, WORD},
// {If, WORD},
// {Then, WORD},
// {Elif, WORD},
// {Else, WORD},
// {DSEMI, WORD},
// {Until, WORD},
// {Case, WORD},
// {WORD, Fi},
	{0, 0, NULL}
};
