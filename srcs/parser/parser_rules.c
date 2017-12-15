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
//	{0, NULL}
};

// const t_case		g_case[] = {
// 	{DSEMI, &cmpdsemi},
// 	{Esac, &cmpesac},
// };

// const t_while		g_while[] = {
// 	{Do, &cmpdo},
// 	{Done, &cmpdone},
// 	{0, NULL}
// };

// const t_if			g_if[] = {
// 	{Then, &cmpthen},
// 	{Else, &cmpelse},
// 	{Elif, &cmpelif},
// 	{Fi, &cmpfi},
// }

// const t_
// const t_first_token g_first_token[] = {
// 		{WORD},
// 		{LPAR},
// 		{If},
// 		{While},
// 		{Until},
// 		{Case},
// 		{0, NULL}
// };