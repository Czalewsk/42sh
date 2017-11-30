/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:04:08 by thugo             #+#    #+#             */
/*   Updated: 2017/11/30 13:50:36 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast_types.h"

/*
**	string (char *); Token id (t_token_id); Token type (t_token_type)
*/

const t_astrule	g_astrules[] = {
	{"&&", AND_IF, OPERATOR},
	{"&", AND, OPERATOR},
	{"(", LPAR, OPERATOR},
	{")", RPAR, OPERATOR},
	{";;", DSEMI, OPERATOR},
	{";", SEMI, OPERATOR},
	{"\n", NEWLINE, OPERATOR},
	{"||", OR_IF, OPERATOR},
	{"|", PIPE, OPERATOR},
	{"<<", DLESS, OPERATOR},
	{">>", DGREAT, OPERATOR},
	{"<&", LESSAND, OPERATOR},
	{">&", GREATAND, OPERATOR},
	{"<<-", DLESSDASH, OPERATOR},
	{"<>", LESSGREAT, OPERATOR},
	{">|", CLOBBER, OPERATOR},
	{"<", LESS, OPERATOR},
	{">", GREAT, OPERATOR},
	{"if", If, RESERVED},
	{"then", Then, RESERVED},
	{"else", Else, RESERVED},
	{"elif", Elif, RESERVED},
	{"fi", Fi, RESERVED},
	{"do", Do, RESERVED},
	{"done", Done, RESERVED},
	{"case", Case, RESERVED},
	{"esac", Esac, RESERVED},
	{"while", While, RESERVED},
	{"until", Until, RESERVED},
	{"for", For, RESERVED},
	{NULL, 0, 0}
};
