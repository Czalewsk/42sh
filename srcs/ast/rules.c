/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:04:08 by thugo             #+#    #+#             */
/*   Updated: 2017/11/29 16:00:53 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast_types.h"

// Token: <<<

const t_astrule	g_astrules[] = {
	{"&&", AND_IF, 0},
	{"&", AND, 0},
	{"(", LPAR, 0},
	{")", RPAR, 0},
	{";;", DSEMI, 0},
	{";", SEMI, 0},
	{"\n", NEWLINE, 0},
	{"||", OR_IF, 0},
	{"|", PIPE, 0},
	{"<<", DLESS, 0},
	{">>", DGREAT, 0},
	{"<&", LESSAND, 0},
	{">&", GREATAND, 0},
	{"<<-", DLESSDASH, 0},
	{"<>", LESSGREAT, 0},
	{">|", CLOBBER, 0},
	{"<", LESS, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{">", GREAT, 0},
	{"while", WHILE, 1, DONE},
	{NULL, 0, 0}
};
