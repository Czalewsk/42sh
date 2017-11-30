/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:04:08 by thugo             #+#    #+#             */
/*   Updated: 2017/11/30 10:35:30 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast_types.h"

const t_astrule	g_astrules[] = {
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
