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
#include "parser.h"

const t_compatibilitytree g_compatibilitytrees[] = {
	{WORD, &cmpword},
	{AND_IF, &cmpand_if},
	{AND, &cmpand},
	{LPAR, &cmplpar},
	{RPAR, &cmprpar},
	{DSEMI, &cmpdsemi},
	{SEMI, &cmpsemi},
	{NEWLINE, &cmpnewline},
	{OR_IF, &cmpor_if},
	{PIPE, &cmppipe},
	{DLESS, &cmpdless},
	{DGREAT, &cmpdgreat},
	{LESSAND, &cmplessand},
	{GREATAND, &cmpgreatand},
	{DLESSDASH, &cmpdlessdash},
	{LESSGREAT, &cmplessgreat},
	{CLOBBER, &cmpclobber},
	{LESS, &cmpless},
	{GREAT, &cmpgreat},
	{If, &cmpif},
	{Then, &cmpthen},
	{Else, &cmpelse},
	{Elif, &cmpelif},
	{Fi, &cmpfi},
	{Do, &cmpdo},
	{Done, &cmpdone},
	{Case, &cmpcase},
	{Esac, &cmpesac},
	{While, &cmpwhile},
	{Until, &cmpuntil},
	{For, &cmpfor},
	{0, NULL}
	// true
	// false
	// in
};

const t_reserved g_reserveds[] = {
//	{If, Fi},
//	{Case, Esac},
	{While, Done},
//	{Until, Done},
//	{For, t_for, Done},
	{0, 0}
};

const t_close_imb g_close_imbs[] = {
	{While, Do, Done},
	{0, 0, 0}
};

const t_modify g_modifys[] = {
	{While},
	{If},
	{Do},
	{Case},
	{For},
	{Until},
	{Then},
	{Elif},
	{Else},
	{Fi},
	{0}
};

const t_excepted g_excepteds[] = {
	{While, While},
	{While, If},
	{While, WORD},
	{Do, WORD},
	{SEMI, WORD},
	{Done, SEMI},
	{Do, SEMI},
	{SEMI, Do},
	{SEMI, Done},
	{SEMI, WORD},
	{AND, WORD},
	{AND_IF, WORD},
	{OR_IF, WORD},
	{PIPE, WORD},
	{AND, While},
	{AND_IF, While},
	{OR_IF, While},
	{PIPE, While},
	{SEMI, While},
	{DLESS, WORD},
	{DGREAT, WORD},
	{LESSAND, WORD},
	{GREATAND, WORD},
	{DLESSDASH, WORD},
	{LESSGREAT, WORD},
	{CLOBBER, WORD},
	{LESS, WORD},
	{GREAT, WORD},
	{WORD, DLESS},
	{WORD, DGREAT},
	{WORD, LESSAND},
	{WORD, GREATAND},
	{WORD, DLESSDASH},
	{WORD, LESSGREAT},
	{WORD, CLOBBER},
	{WORD, LESS},
	{WORD, GREAT},
	{WORD, AND_IF},
	{WORD, OR_IF},
	{WORD, AND},
	{WORD, SEMI},
	{WORD, PIPE},
	{WORD, WORD},
	// {Case, WORD},
	// {If, WORD},
	// {Then, WORD},
	// {Elif, WORD},
	// {Else, WORD},
	// {DSEMI, WORD},
	// {Until, WORD},
	// {Case, WORD},
	// {WORD, Fi},
	{0, 0}
};
