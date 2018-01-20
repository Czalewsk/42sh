/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_fn2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:44:48 by thugo             #+#    #+#             */
/*   Updated: 2018/01/19 19:04:24 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_types.h"

int		rules_word(t_token *tk, char **cur, char *escape)
{
	if (!*escape && (**cur == ' ' || **cur == '\t' || **cur == '\n'))
	{
		++*cur;
		if (tk->size)
			return (1);
	}
	else
	{
		if (!tk->size)
		{
			tk->id = WORD;
			tk->str = *cur;
		}
		++tk->size;
		++*cur;
	}
	return (0);
}

/*
**	Flags:
**		1: Simple quote '
**		2: Double quote "
**		4: Backslash \
**		8: Backslash counter
*/

int		rules_escape(t_token *tk, char **cur, char *escape)
{
	(void)tk;
	if (*escape & 8)
	{
		if (**cur != '\n')
			*escape &= ~(char)8;
	}
	else if (*escape & 4)
		*escape &= ~(char)4;
	if (!(*escape & (char)(2 | 4)) && **cur == '\'')
		*escape ^= 1;
	else if (!(*escape & (char)(1 | 4)) && **cur == '"')
		*escape ^= 2;
	else if (!(*escape & (char)(1 | 4)) && **cur == '\\')
		*escape |= (char)(4 | 8);
	return (0);
}
