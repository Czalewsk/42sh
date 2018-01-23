/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:04:08 by thugo             #+#    #+#             */
/*   Updated: 2018/01/12 16:45:45 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast_types.h"

/*
**	string (char *); Token id (t_token_id);
*/

const t_token_assign	g_token_operator[] = {
	{"&&", AND_IF},
	{"&", AND},
	{"(", LPAR},
	{")", RPAR},
	{";;", DSEMI},
	{";", SEMI},
	{"\n", NEWLINE},
	{"||", OR_IF},
	{"|", PIPE},
	{"<<", DLESS},
	{">>", DGREAT},
	{"<&", LESSAND},
	{">&", GREATAND},
	{"<<-", DLESSDASH},
	{"<>", LESSGREAT},
	{">|", CLOBBER},
	{"<", LESS},
	{">", GREAT},
	{NULL, 0}
};

const t_token_assign	g_token_reserved[] = {
	{"if", If},
	{"then", Then},
	{"else", Else},
	{"elif", Elif},
	{"fi", Fi},
	{"done", Done},
	{"do", Do},
	{"case", Case},
	{"esac", Esac},
	{"while", While},
	{"until", Until},
	{"for", For},
	{NULL, 0}
};
